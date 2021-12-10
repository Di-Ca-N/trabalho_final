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

As interações entre todos esses módulos são gerenciadas pelo módulo principal main.

## Funcionalidades
- Menu inicial com as opções "Novo Jogo", "Carregar jogo", "Ranking" e "Sair"
- Exibição do jogo
- Movimentação do Dave, tanto caminhando quanto voando com o jetpack
- Coleta de itens
- Processamento da pontuação do jogador
- Morte e _respawn_ do Dave
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

## Recursos utilizados

| Recurso                          | Autor    | Licença                                                             | URL    | Acesso em
|-------------------               |----------|----------------------                                               |-----   |-----
|Gemas, coroa, chapéu e background | Brackeys |[Standard Unity Asset Store EULA](https://unity3d.com/legal/as_terms)| https://assetstore.unity.com/packages/2d/free-2d-mega-pack-177430 | 15/11/2021
|Sprites de água e lava            | BlueFoxx_ | [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/)| https://opengameart.org/content/16x16-water-lava-sprites | 15/11/2021
|Anel e troféu                     | Alex's Assets| [CC0](https://creativecommons.org/publicdomain/zero/1.0/deed.pt_BR) | https://alexs-assets.itch.io/16x16-rpg-item-pack | 15/11/2021
|Porta (Modificada)                | o lobster | [CC0](https://creativecommons.org/publicdomain/zero/1.0/deed.pt_BR)| https://o-lobster.itch.io/simple-dungeon-crawler-16x16-pixel-pack | 15/11/2021
| Personagem                       |route1rodent | [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/) | https://route1rodent.itch.io/16x16-rpg-character-sprite-sheet | 15/11/2021
