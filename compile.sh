gcc -o main -std=c99 -g -pedantic -Wall -Wextra main.c vect.c obj.c movement.c objlist.c draw.c -lm `pkg-config --cflags --libs allegro-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_primitives-5.0`
chmod +x main
echo "compilation complete"
