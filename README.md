# Süpermarket Navigasyon Uygulaması (Supermarket Navigation App)

Bu proje, bir süpermarketteki bir ürünü en kısa yoldan bulmaya yarayan bir yol bulma (pathfinding) uygulamasıdır. Kullanıcı, almak istediği ürünleri seçtikten sonra uygulama, başlangıç noktasından (kapı) başlayarak bu ürüne en kısa rotayı bulur.

## Özellikler (Features)
- Açgözlü en iyi öncelikli arama (greedy best first search) algoritmasını kullanır.
- Sadece sezgisel fonksiyonu kullanır. Sezgisel fonksiyon öklid mesafesi olarak alınmıştır.
- Süpermarket krokisi, düğümler (nodes) ve koordinatları ile temsil edilir.
- Kullanıcıdan almak istediği ürün alınır.
- Komut satırı tabanlıdır.

## Derleme ve Çalıştırma (Build and Run)

```bash
gcc -o supermarket_pathfinder supermarket_pathfindert.c -lm


