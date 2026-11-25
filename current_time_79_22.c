#include <stdio.h>
#include <time.h>

#define DEFAULT_LOG "/tmp/current_time.log"

int main(int argc, char *argv[])
{
    const char *log_path = (argc > 1) ? argv[1] : DEFAULT_LOG;
    char buf[64];
    time_t now = time(NULL);
    struct tm tm_now;

    if (localtime_r(&now, &tm_now) == NULL) {
        fprintf(stderr, "localtime_r: помилка\n");
        return 1;
    }
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm_now);

    /* "a" - дописуємо в кінець, щоб зберігалась історія запусків */
    FILE *f = fopen(log_path, "a");
    if (f == NULL) {
        perror(log_path);
        return 1;
    }
    fprintf(f, "Поточний час: %s\n", buf);
    fclose(f);
    return 0;
}
