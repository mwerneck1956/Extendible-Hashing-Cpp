echo "Começando a compilação do projeto"

g++ ./Classes/Directory/Directory.cpp ./Classes/Bucket/Bucket.cpp main.cpp -o main
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
else
   echo "nao compilado"
fi
