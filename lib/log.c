#include <stdio.h>
#include <stdarg.h>

FILE *log_file = NULL;

#define ENSURE_FP() if (log_file == NULL) { log_file = stdout; }

void flux_log_file_set(const char *file_path) {
  if (log_file == NULL) {
    log_file = fopen(file_path, "w");
  }
}

void flux_log(const char *format, ...) {
  ENSURE_FP();

  va_list args;
  va_start(args, format);
  vfprintf(log_file, format, args);
  va_end(args);
  fflush(log_file);
}

void flux_log_mem(void *ptr, const char *format, ...) {
  ENSURE_FP();

  // Prefix the line with the memory address
  fprintf(log_file, "%x: ", ptr);

  va_list args;
  va_start(args, format);
  vfprintf(log_file, format, args);
  va_end(args);
  fflush(log_file);
}

// TODO: Add a logger with indentation --
// printf("%*s%s", indent, "", string);
