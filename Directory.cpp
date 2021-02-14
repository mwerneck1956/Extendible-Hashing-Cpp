#include "./Directory.h"

Directory::Directory(int number_of_bits, int bucket_max_size)
{
    this->number_of_bits = number_of_bits;
    this->bucket_max_size = bucket_max_size;

    //Por conveniência inicializo o global_depth com 2
    this->global_depth = 2;

    //Adiciono o primeiro balde
    Bucket *firstBucket = new Bucket(bucket_max_size);

    //Faz todas posições do meu balde apontarem para o mesmo Bucket
    for (int i = 0; i < pow(2, this->global_depth); i++)
    {
        this->buckets.push_back(firstBucket);
    }
}
//Transforma um valor inteiro em binário(bitwize)
string Directory::hash(long long int value , int number_of_btis) 
{
    string hashedValue;
    for (int i = number_of_bits - 1; i >= 0; i--)
    {
        long long int k = value >> i;
        if (k & 1)
            hashedValue.push_back('1');
        else
            hashedValue.push_back('0');
    }
    return hashedValue;
}

long int Directory::binary_to_decimal(long int n)
{
    int decimal = 0, i = 0, remainder;
    while (n != 0)
    {
        remainder = n%10;
        n /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }

    return decimal;
}

void Directory::Insert(long long int value)
{
    string hashedValue = this->hash(value , this->number_of_bits);
    //Pego as posições significativas da chave que serão relativas ao global_depth
    string significantBits = hashedValue.substr(0, this->global_depth);
    //Pego os bits mais significativos para achar em que posição do meu diretório o valor vai ficar
    int valueIndex = this->binary_to_decimal(stoi(significantBits));

    if (!this->buckets[valueIndex]->IsFull())
    {
        this->buckets[valueIndex]->Insert(hashedValue, this->global_depth);
    }
    else if (this->buckets[valueIndex]->IsFull() && this->global_depth > this->buckets[valueIndex]->GetLocalDepth())
    {
        Bucket *newBucket = new Bucket(this->bucket_max_size);

        //Insiro o novo valor no novo balde´
        newBucket->Insert(hashedValue, global_depth);

        this->buckets[valueIndex]->PrintBucket();

        //Guarda os valores que vão ser inseridos no novo balde, e depois vão ter que
        //ser removidos do antigo balde.
        vector<string> insertedValues;
        insertedValues.reserve(this->bucket_max_size);

        for (int i = 0; i < this->buckets[valueIndex]->GetSize(); i++)
        {
            //Se o valor que estou passando tiver os bits significativos igual do valor a ser inserido
            //vou remover ele do balde original e guardar no meu novo balde
            if (this->buckets[valueIndex]->GetElement(i).substr(0, this->global_depth) == significantBits)
            {
                newBucket->Insert(this->buckets[valueIndex]->GetElement(i), this->global_depth);
                //Adiciono no meu vetor de inseridos ´para remover o valor do meu balde antigo
                insertedValues.push_back(this->buckets[valueIndex]->GetElement(i));
            }
        }

        cout << "Valores inseridos : ";
        for(int i = 0 ; i < insertedValues.size() ;i++)
        cout << insertedValues.at(i) << " ";
        cout << endl;


        cout << "Balde antigo antes remocao" << endl;
        this->buckets[valueIndex]->PrintBucket();
        cout << endl;


        //Removo valores inseridos no balde novo do meu balde antigo
        for(string value : insertedValues)
            this->buckets[valueIndex]->Remove(value,this->global_depth);

        cout << "Balde antigo " << endl;
        this->buckets[valueIndex]->PrintBucket();
        cout << endl;

        cout << "Balde novo " << endl;
        newBucket->PrintBucket();
        cout << endl;

        this->buckets[valueIndex] = newBucket;

        
    }
}

bool Directory::Find(long long int value)
{
    //Aplico a função de hash no valor obtido
    string hashedValue = this->hash(value,this->number_of_bits);

    //Pego os bits significativos do valor para saber
    //posição do diretório que ele deverá ocupar se existirr
    string signficantBits = hashedValue.substr(0,this->global_depth);
    long int position = this->binary_to_decimal(stoi(signficantBits));

    //Acesso a posição no meu diretório, se exister e proucuro pela chave no balde
    if(this->buckets[position] != NULL){
        if(this->buckets[position]->Find(hashedValue) != -1)
            return true;
    }       

    //Se o indice for invalido ou o valor não existir no balde retorno falso
    return false;
}

void Directory::DuplicateDirectory(){
    for(int i = pow(2,this->global_depth) ; i < pow(2,this->global_depth + 1); i++){
        this->buckets.push_back(NULL);
    }
    this->global_depth++;
    Bucket* auxBucket;
    //Reorganizo os ponteiros
    for(int i = 0 ; i <= pow(2,this->global_depth)/2 ; i++){
        auxBucket = this->buckets[i+1];
        this->buckets[i+1] = this->buckets[i];
        this->buckets[i+2] = auxBucket;
    }
    //Faço o ultimo apontar para o balde do  ante penultimo
    
    this->buckets[pow(2,this->global_depth)] = this->buckets[pow(2,this->global_depth -1)];
}

void Directory::PrintInfo()
{
    for (int i = 0; i < this->buckets.size(); i++)
    {
        if (this->buckets[i])
        {
            cout << "Diretório : " << i << endl;
            cout << "Valores : ";
            int bucketSize = this->buckets[i]->GetSize();
            for (int j = 0; j < bucketSize; j++)
            {
                cout << this->buckets[i]->GetElement(j) + " ,";
            }
            cout << endl;
        }
    }
}