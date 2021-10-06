Map gerarMapa() {
    Map map;

    map.height = 20;
    map.width = 80;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 80; j++) {
            map.stage[i][j] = 'x';
        }
    }
    map.daveStart[0] = 2;
    map.daveStart[1] = 4;
    return map;
}

int main() {
    Map mapa = gerarMapa();
    printf("Altura do mapa: %d\n", mapa.height);
    
    for (int i = 0; i < mapa.height; i++) {
        for (int j = 0; j < mapa.width; j++) {
            printf("%c", mapa.stage[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}