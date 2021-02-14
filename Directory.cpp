#include "./Directory.h"

Directory::Directory(int number_of_bits, int bucket_max_size)
{
    this->number_of_bits = number_of_bits;
    this->bucket_max_size = bucket_max_size;
    this->single_buckets =0;
    //Por conveniência inicializo o global_depth com 2
    this->global_depth = 2;

    //Adiciono o primeiro balde
    Bucket *firstBucket = new Bucket(bucket_max_size);
    this->single_buckets++;

    //Faz todas posições do meu balde apontarem para o mesmo Bucket
    for (int i = 0; i < pow(2, this->global_depth); i++)
    {
        this->buckets.push_back(firstBucket);
    }
}
//Transforma um valor inteiro em binário(bitwize)
string Directory::hash(long long int value, int number_of_btis)
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
        remainder = n % 10;
        n /= 10;
        decimal += remainder * pow(2, i);
        ++i;
    }

    return decimal;
}

void Directory::Insert(long long int value)
{
    string hashedValue = this->hash(value, this->number_of_bits);
    //Pego as posições significativas da chave que serão relativas ao global_depth
    string significantBits = hashedValue.substr(0, this->global_depth);
    //Pego os bits mais significativos para achar em que posição do meu diretório o valor vai ficar
    int valueIndex = this->binary_to_decimal(stoll(significantBits));

    if (!this->buckets[valueIndex]->IsFull())
    {
        this->buckets[valueIndex]->Insert(hashedValue, this->global_depth);
    }
    //Caso médio
    else if (this->buckets[valueIndex]->IsFull() && this->global_depth > this->buckets[valueIndex]->GetLocalDepth())
    {
        Bucket *newBucket = new Bucket(this->bucket_max_size);
        this->single_buckets++;

        //Insiro o novo valor no novo balde
        newBucket->Insert(hashedValue, global_depth);

        //Guarda os valores que vão ser inseridos no novo balde, e depois vão ter que
        //ser removidos do antigo balde.
        vector<string> insertedValues;
        insertedValues.reserve(this->bucket_max_size);

        for (int i = 0; i < this->buckets[valueIndex]->GetUsedSize(); i++)
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

        //Removo valores inseridos no balde novo do meu balde antigo
        for (string value : insertedValues)
        {
            this->buckets[valueIndex]->Remove(value, this->global_depth);
        }

        this->buckets[valueIndex] = newBucket;
    }
    //pior caso
    else
    {
        //Duplico meu diretório
        this->DuplicateDirectory();

        //Como o balde foi duplicado altero o valor dos bits significantes da minha hash
        significantBits = hashedValue.substr(0, this->global_depth);

        int elementPosition = this->binary_to_decimal(stoll(significantBits));

        //Crio um novo balde
        Bucket *newBucket = new Bucket(this->bucket_max_size);
        this->single_buckets++;

        //Insiro o novo valor nele
        newBucket->Insert(hashedValue, this->global_depth);

        //Vetor auxiliar para guardar os valores que irão ser inseridos no novo balde
        //e posteriormente deletados do balde antigo
        vector<string> insertedValues;
        insertedValues.reserve(this->bucket_max_size);
        //Pego todas as chaves com bits significativos iguais a da ser inserida e jogo em um novo balde
        for (int i = 0; i < this->buckets[elementPosition]->GetUsedSize(); i++)
        {
            //Se os bits significativos da chave são iguais ao do comparado insiro no novo balde
            if (this->buckets[elementPosition]->GetElement(i).substr(0, this->global_depth) == significantBits)
            {
                newBucket->Insert(this->buckets[elementPosition]->GetElement(i), this->global_depth);
                insertedValues.push_back(this->buckets[elementPosition]->GetElement(i));
            }
        }
        //Removo valores inseridos no balde novo do meu balde antigo
        for (string value : insertedValues)
            this->buckets[elementPosition]->Remove(value, this->global_depth);

        //Faço meu diretório da posição atual apontar par o novo balde
        this->buckets[elementPosition] = newBucket;
    }
}

bool Directory::Find(long long int value)
{
    //Aplico a função de hash no valor obtido
    string hashedValue = this->hash(value, this->number_of_bits);

    //Pego os bits significativos do valor para saber
    //posição do diretório que ele deverá ocupar se existirr
    string signficantBits = hashedValue.substr(0, this->global_depth);
    long int position = this->binary_to_decimal(stoll(signficantBits));

    //Acesso a posição no meu diretório, se exister e proucuro pela chave no balde
    if (this->buckets[position] != NULL)
    {
        if (this->buckets[position]->Find(hashedValue) != -1)
            return true;
    }

    //Se o indice for invalido ou o valor não existir no balde retorno falso
    return false;
}

int Directory::getNumberOfBuckets()
{
    return this->single_buckets;
}

void Directory::DuplicateDirectory()
{

    //Faço uma cópia do meu vetor de buckets
    vector<Bucket *> bucketsCopy = this->buckets;

    for (int i = pow(2, this->global_depth); i < pow(2, this->global_depth + 1); i++)
    {
        this->single_buckets++;
        this->buckets.push_back(NULL);
    }

    this->global_depth++;
    int j = 0;

    //Reorganização dos ponteiros

    //Itero todo meu vetor de baldes e, rearranjo os ponteiros relacionando
    //os ponteiros do diretório duplicado com o diretório original
    //exemplo, v[0] e v[1] irão receber [0] do copiado
    //exemplo, v[2] e v[3] irão receber [1] do copiado
    //exemplo, v[4] e v[5] irão receber [2] do copiado
    //exemplo, v[6] e v[7] irão receber [3] do copiado
    for (int i = 0; i < pow(2, this->global_depth); i += 2)
    {
        this->buckets[i] = bucketsCopy[j];
        this->buckets[i + 1] = bucketsCopy[j];
        j++;
    }

    //Deleto meu vetor auxiliar dos baldes copiados
    bucketsCopy.clear();
    bucketsCopy.shrink_to_fit();
}

void Directory::PrintInfo()
{
    for (int i = 0; i < this->buckets.size(); i++)
    {
        if (this->buckets[i])
        {
            cout << "Diretório : " << i << endl;
            cout << "Valores : ";
            int bucketSize = this->buckets[i]->GetUsedSize();
            for (int j = 0; j < bucketSize; j++)
            {
                cout << this->buckets[i]->GetElement(j) + " ,";
            }
            cout << endl;
        }
    }
}

Directory::~Directory()
{
    this->buckets.~vector();
    delete &this->global_depth;
    delete &this->number_of_bits;
    delete &this->bucket_max_size;
}