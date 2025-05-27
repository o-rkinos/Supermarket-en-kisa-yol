#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MAX_NODES 31 // 30 tane raf + kapı

// Koordinat yapısı
typedef struct {
    double x, y;
} Point;

// Düğümlerin koordinatları (0 = kapi)
Point coordinates[MAX_NODES] = {
    {0, 6.5},      // 0 = kapi
    {1.5, 1.5},    // 1
    {7, 4},        // 2
    {11, 17},      // 3
    {11, 14.5},    // 4
    {11, 14.5},    // 5
    {11, 11.5},    // 6
    {11, 11.5},    // 7
    {11, 9},       // 8
    {12.5, 1.5},   // 9
    {17.5, 6},     // 10
    {17.5, 1.5},   // 11
    {23, 17},      // 12
    {23, 14.5},    // 13
    {23, 14.5},    // 14
    {23, 11.5},    // 15
    {23, 11.5},    // 16
    {23, 9},       // 17
    {26.5, 6},     // 18
    {24, 1.5},     // 19
    {30.5, 1.5},   // 20
    {35, 17},      // 21
    {35, 14.5},    // 22
    {35, 14.5},    // 23
    {35, 11.5},    // 24
    {35, 11.5},    // 25
    {35, 9},       // 26
    {34.5, 6},     // 27
    {36.5, 1.5},   // 28
    {45.5, 13.5},  // 29
    {44.5, 4}      // 30
};

// Komşuluk listesi yapısı
typedef struct {
    int neighbors[30];
    int count;
} AdjList;

AdjList graph[MAX_NODES];

// Eklenecek tüm kenarlar (tüm birbirine bağlı iki düğümler)
int edges[][2] = {
    {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},
    {1,2},
    {2,3},{2,4},{2,5},{2,6},{2,7},{2,8},{2,9},{2,10},
    {3,4},{3,5},{3,6},{3,7},{3,8},{3,10},{3,12},{3,13},{3,14},{3,15},{3,16},{3,17},
    {4,3}, {4,5},{4,6},{4,7},{4,8},{4,10},{4,12},{4,13},{4,14},{4,15},{4,16},{4,17},
    {5,3},{5,4},{5,6},{5,7},{5,8},{5,10},{5,12},{5,13},{5,14},{5,15},{5,16},{5,17},
    {6,3},{6,4},{6,5},{6,7},{6,8},{6,10},{6,12},{6,13},{6,14},{6,15},{6,16},{6,17},
    {7,3},{7,4},{7,5},{7,6},{7,8},{7,10},{7,12},{7,13},{7,14},{7,15},{7,16},{7,17},
    {8,3},{8,4},{8,5},{8,6},{8,7},{8,9},{8,10},{8,12},{8,13},{8,14},{8,15},{8,16},{8,17},{8,6},{8,10},
    {9,10},{9,11},
    {10,11},{10,12},{10,13},{10,14},{10,15},{10,16},{10,17},{10,18},{10,19},
    {11,10},{11,18},{11,19},
    {12,13},{12,14},{12,15},{12,16},{12,17},{12,18},{12,21},{12,22},{12,23},{12,24},{12,25},{12,26},
    {13,12},{13,14},{13,15},{13,16},{13,17},{13,18},{13,21},{13,22},{13,23},{13,24},{13,25},{13,26},
    {14,12},{14,13},{14,15},{14,16},{14,17},{14,18},{14,21},{14,22},{14,23},{14,24},{14,25},{14,26},
    {15,12},{15,13},{15,14},{15,16},{15,17},{15,18},{15,21},{15,22},{15,23},{15,24},{15,25},{15,26},
    {16,12},{16,13},{16,14},{16,15},{16,17},{16,18},{16,21},{16,22},{16,23},{16,24},{16,25},{16,26},
    {17,12},{17,13},{17,14},{17,15},{17,16},{17,18},{17,21},{17,22},{17,23},{17,24},{17,25},{17,26},
    {18,19},{18,20},{18,21},{18,22},{18,23},{18,24},{18,25},{18,26},{18,27},
    {19,20},{19,18},
    {20,18},{20,27},{20,28},
    {21,22},{21,23},{21,24},{21,25},{21,26},{21,27},{21,29},
    {22,21},{22,23},{22,24},{22,25},{22,26},{22,27},{22,29},
    {23,21},{23,22},{23,24},{23,25},{23,26},{23,27},{23,29},
    {24,21},{24,22},{24,23},{24,25},{24,26},{24,27},{24,29},
    {25,21},{25,22},{25,23},{25,24},{25,26},{25,27},{25,29},
    {26,21},{26,22},{26,23},{26,24},{26,25},{26,27},{26,29},{26,30},
    {27,28},{27,29},{27,30},
    {28,27},{28,30},
    {29,30},
    {30,29}
};

const char* nodeNames[MAX_NODES] = {
    "Kapi",                     // 0
    "Dergi, Kitap",             // 1
    "Manav",                    // 2
    "Yapi-Market, Hirdavat",    // 3
    "Cikolata",                 // 4
    "Cips, Kek, Kraker",        // 5
    "Cerez",                    // 6
    "Alkollu icecek",           // 7
    "Yogurt, Kahvaltilik",      // 8
    "Balik",                    // 9
    "Sarkuteri",                // 10
    "Kirmizi et",               // 11
    "Oyuncak",                  // 12
    "Temizlik Malzemeleri",     // 13
    "Temizlik Malzemeleri",     // 14
    "Su",                       // 15
    "Gazli icecek, Meyve Suyu", // 16
    "Sut, Kahvaltilik Gevrek",  // 17
    "Kuruyemis, Meze",          // 18
    "Tavuk",                    // 19
    "Taze firin",               // 20
    "Bebek Bezi, Mama",         // 21
    "Un, Makarna",              // 22
    "Yag, Konserve, Sos",       // 23
    "Bakliyat",                 // 24
    "Cay, Kahve, Seker",        // 25
    "Tatli",                    // 26
    "Dondurulmus Gida",         // 27
    "Hazir Firin",              // 28
    "Kisisel Bakim",            // 29
    "Mutfak Gerecleri"          // 30
};

// Graf yapısı. Kenarların hepsi çift yönlü ekleniyor
void buildGraph() {
    int totalEdges = sizeof(edges) / sizeof(edges[0]);//kenarların toplam bayt'ı / bir kenarın bayt'ı = toplam komşuluk(kenar) sayısı
    for (int i = 0; i < totalEdges; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        graph[a].neighbors[graph[a].count++] = b;//Düğüm a, düğüm b ile bağlantılıdır. Bu bilgiyi a'nın komşuları listesine ekle
        graph[b].neighbors[graph[b].count++] = a;//Düğüm `b`, düğüm `a` ile bağlantılıdır. Bu bilgiyi `b`'nin komşuları listesine ekle
    }
}

// Sezgisel (heuristic) fonksiyon için hedef düğüm ile mevcut düğüm arasındaki kuşuçumu mesafe (Öklid mesafesi)
double heuristic(int node, int goal) {
    double dx = coordinates[node].x - coordinates[goal].x;
    double dy = coordinates[node].y - coordinates[goal].y;
    return sqrt(dx * dx + dy * dy);
}

// En küçük sezgiseli buluyoruz
int findLowestHeuristic(bool visited[], int open[], int openSize, int goal) {
    int bestIndex = -1;
    double bestHeuristic = 1e9;//çok büyük bir sayı
    for (int i = 0; i < openSize; i++) {//openSize: open[] dizisinde kaç tane düğüm olduğunu belirtir
        int node = open[i];
        if (!visited[node]) {//bu düğüm daha önce ziyaret edilmediyse (visited[node] = false ise)
            double distance = heuristic(node, goal);
            if (distance < bestHeuristic) {//bestHeuristic değerinden daha küçük bir heuristic değeri bulunursa, o düğüm bestHeuristic değişkenine atanacak, index'i de bestIndex değişkenine atanacak
                bestHeuristic = distance;
                bestIndex = i;
            }
        }
    }
    return bestIndex;
}

void bestFirstSearch(int start, int goal) {
    bool visited[MAX_NODES] = {false};//Bu dizi her düğümün ziyaret edilip edilmediğini tutar, hepsi başlangıçta false olarak ayarlanır.
    int parent[MAX_NODES];//Bu düğüme hangi düğümden geldik?
    for (int i = 0; i < MAX_NODES; i++) parent[i] = -1;//Başta tüm düğümler -1 ile işaretlenir
    int open[MAX_NODES];//Şu anda değerlendirmeye açık düğümler.
    int openSize = 0;

    open[0] = start; openSize=1; //Başlangıç düğümü ( 0 = Kapı) open[] listesine eklenir.

    while (openSize > 0) {
        int bestIndex = findLowestHeuristic(visited, open, openSize, goal);//open[] içinde en iyi adayı bulur
        if (bestIndex == -1) break;//Eğer geçerli düğüm kalmadıysa (tüm yollar tükenmişse) döngü sona erer.

        int current = open[bestIndex];//Şu anda işlenecek olan düğüm current
        open[bestIndex] = open[--openSize];//current düğümünü open[] listesinden çıkarılır, listenin sonundaki düğümü bestIndex konumuna alarak yer değiştirir.

        visited[current] = true;//Şimdi bu düğüm ziyaret edildi olarak işaretlenir.
        if (current == goal) break;//Eğer hedefe ulaşıldıysa (current hedef düğümse), arama sona erer

        for (int i = 0; i < graph[current].count; i++) {//Mevcut düğümün (current) komşuları sırayla ele alınır
            int neighbor = graph[current].neighbors[i];
            if (!visited[neighbor]) {//Eğer bu komşu daha önce ziyaret edilmemişse işlem yapılır.
                bool inOpen = false;
                for (int j = 0; j < openSize; j++) {//Komşu zaten open[] dizisindeyse tekrar eklenmez
                    if (open[j] == neighbor) {
                        inOpen = true;
                        break;
                    }
                }
                if (!inOpen) {
                    open[openSize++] = neighbor;//Komşu open[] dizisinde yoksa eklenir
                    if (parent[neighbor] == -1) {
                        parent[neighbor] = current;//Daha önce parent'ı atanmadıysa, parent'ı olarak current atanır.
                    }
                }
            }
        }
    }

    // Yolu yazdır. Goal(hedef) düğümünden kapıya kadar parent[] dizisine tersten yol yazılır.
    int path[MAX_NODES];
    int pathSize = 0;
    for (int current = goal; current != -1; current = parent[current]) {
        path[pathSize++] = current;
    }
    printf("Gidilecek yol: \n");
    for (int i = pathSize - 1; i >= 0; i--) {
        printf("%s%s", nodeNames[path[i]], i ? " -> " : "\n");
    }
    for (int i = pathSize - 1; i >= 0; i--) {
        printf("%d%s", path[i], i ? " -> " : "\n");
    }
}

void printMenu() {
    printf("\n=========================================\n");
    printf("           ALISVERIS REHBERI\n");
    printf("=========================================\n");

    for (int i = 0; i < MAX_NODES; i++) {
        printf("%2d - %s\n", i, nodeNames[i]);
    }

    printf("=========================================\n");
}

int main() {
    buildGraph();
    int hedef;
    printMenu();
    printf("Hedef urun numarasini girin (1-30): ");
    scanf("%d", &hedef);
    if (hedef < 1 || hedef > 30) {
        printf("Gecersiz hedef!\n");
        return 1;
    }
    bestFirstSearch(0, hedef);

    getchar(); getchar();
    return 0;
}
