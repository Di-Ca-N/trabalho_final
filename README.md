# Dangerous Dave

Jogo desenvolvido como trabalho final do componente curricular "Algoritmos e Programação", ministrado pelo Prof. Lucas Rafael Costella Pessutto. Esse jogo é inspirado em [Dangerous Dave](https://en.wikipedia.org/wiki/Dangerous_Dave), um jogo de 1988 desenvolvido por John Romero.

## Bibliotecas utilizadas
- [raylib](https://www.raylib.com/) 3.7

## Estrutura do projeto
O projeto está organizado em seis módulos com responsabilidades distintas:
- game: Lógica central do jogo (movimentação de personagem, itens, pontuação, progressão de fase...)
- graphics: Exibição do jogo e demais componentes na tela
- ranking: Gerenciamento do ranking de pontuações
- maps: Carregamento e manipulação dos mapas do jogo
- saves: Salvamento e carregamento do jogo
- menus: Funcionalidade dos menus do jogo

As interações entre todos esses módulos são gerenciadas pelo módulo principal main;

## Funcionalidades implementadas
- Menu inicial com as opções "Novo Jogo", "Carregar jogo", "Ranking" e "Sair"
- Exibição do jogo
- Movimentação do Dave, tanto caminhando quanto voando com o jetpack
- Coleta de itens
- Processamento da pontuação do jogador
- Morte e respawn do Dave
- Salvamento e carregamento do jogo
- Persistência do ranking
- Passar de fase
- Fim de jogo
- Confirmação de saída
- Adição do nome do jogador no ranking

## Compilação

Para compilar esse projeto, recomenda-se a utilização de [CMake](https://cmake.org/).

### MinGW
Na raíz do projeto, execute os seguintes comandos:

```
cmake . -G "MinGW Makefiles"
mingw32-make
```

Atenção: Devido a limitações do MinGW, o caminho do projeto não pode conter caracteres não ASCII (como letras com acentos ou cedilha).

### Linux
```
cmake .
make
```