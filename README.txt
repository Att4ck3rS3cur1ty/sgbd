Sistema Gerenciador de Banco de Dados - Exemplo (com vários bugs)
===========================================================================================
 
- Funções implementadas:

    1 - Criar tabelas
    2 - Listar todas as tabelas
    3 - Criar uma nova linha na tabela
    4 - Listar todos os dados de uma tabela
    5 - Pesquisar valor em uma tabela
    6 - Apagar o valor de uma tabela
    7 - Apagar uma tabela
    8 - Sair

- Como compilar o programa: 

    Utilizando o terminal do Linux, basta inserir o seguinte comando para efetuar a compilação:
        gcc *.c -o nome_executavel

    Ainda utilizando o terminal do Linux, basta executar o programa, da seguinte maneira:
        ./nome_executavel

- O que eu faria diferente:

    Os parâmetros dos loops while poderiam ter sido melhor planejados ao invés de deixar 
    somente while(1), o que é uma falha de segurança dentro de um projeto que utilize a linguagem C. 

    Caso houvesse mais tempo, eu teria feito mais "idiot-proof" para testar todas as entradas possíveis
    que o programa poderia receber e, dessa forma, reverter os erros, caso não sejam feitas as entradas 
    previamente esperadas. 




