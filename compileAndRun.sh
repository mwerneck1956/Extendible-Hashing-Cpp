echo "Começando a compilação do projeto"

g++ -o main *.cpp
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
   echo "executando o projeto..."
   ./main 
else
   echo "nao compilado"
fi