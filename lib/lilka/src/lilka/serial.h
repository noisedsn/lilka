#ifndef LILKA_SERIAL_H
#define LILKA_SERIAL_H

namespace lilka {

void serial_begin();
void serial_log(const char *message, ...);

} // namespace lilka

#endif // LILKA_SERIAL_H
