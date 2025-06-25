# Lanchonete em C

Este projeto foi desenvolvido na linguagem C com a intenção de simular o funcionamento básico de uma lanchonete inspirado nós sistemas de autoatendimento do McDonald's, ou seja, permitir que o usuário visualize o cardápio, faça pedidos, calcule o valor total e finalize a compra,tudo dentro do próprio estabelecimento.É um sistema simples, mas que nos ajuda a aplicar vários conceitos aprendidos nas aulas de Algoritmos e Programação.

O programa começa incluindo algumas bibliotecas importantes como stdio.h, stdlib.h, string.h, e também outras como windows.h e conio.h, que são usadas para fazer algumas melhorias visuais no console, como mudar a cor do texto e controlar o cursor. Isso dá uma cara mais interativa pro sistema, mesmo sendo tudo em modo texto.

Uma das partes que mais interessante foi a função BarraProgressao(), que simula uma barra de carregamento. Achei legal porque ela dá uma sensação de “profissionalismo”, como se o programa estivesse iniciando de verdade. Não serve pra nada funcional no código, mas ajuda na experiência de quem tá usando.

Depois disso, o sistema exibe um menu principal com opções para o usuário escolher. Ele pode ver o cardápio, fazer pedidos,ver o total ou sair,um sistema de segurança onde o funcionário teria que colocar uma senha para poder fazer as mudanças,onde teria o total de 3 tentativas para inserir a senha correta. Tudo isso funciona usando estruturas como switch e while, que são essenciais pra controlar o fluxo do programa e deixar ele reagir às escolhas do usuário.

O código também está dividido em várias funções, o que deixa tudo mais organizado e mais fácil de entender. Por exemplo, tem uma função só pra mostrar o cardápio, outra pra calcular o valor da compra, outra pra mostrar o pedido finalizado e assim por diante. Isso é algo que o professor sempre fala pra gente fazer: separar o código em partes menores e com funções bem definidas.

Outra coisa legal é como o programa cuida da parte visual, como imprimir os elementos em posições específicas do console, usar cores diferentes e centralizar textos. Tudo isso foi feito usando a biblioteca windows.h, que tem funções como SetConsoleCursorPosition e SetConsoleTextAttribute. Isso não é algo que usamos sempre, mas torna a experiência mais agradável.

No geral, esse projeto foi muito útil pra praticar o uso de funções, condicionais, laços de repetição, vetores, variáveis e até um pouco de estética no terminal. Mesmo sendo um projeto simples, ele representa bem o que a gente aprendeu até agora e me ajudou a entender como a programação pode ser usada pra simular situações do dia a dia, como o atendimento numa lanchonete.

1º período - allen
Curso: engenharia de software 