/*
      _   ___ ___  _   _ ___ _  _  ___  _    ___   ___
     /_\ | _ \   \| | | |_ _| \| |/ _ \| |  / _ \ / __|
    / _ \|   / |) | |_| || || .` | (_) | |_| (_) | (_ |
   /_/ \_\_|_\___/ \___/|___|_|\_|\___/|____\___/ \___|
    Log library for Arduino
    version 1.1.1
    https://github.com/thijse/Arduino-Log
    Licensed under the MIT License <http://opensource.org/licenses/MIT>.
*/

#include "ArduinoLog.h"

void Logging::begin(int level, Print *logOutput, bool showLevel) {
#ifndef DISABLE_LOGGING
    setLevel(level);
    setShowLevel(showLevel);
    _logOutput = logOutput;
#endif
}

void Logging::setLevel(int level) {
#ifndef DISABLE_LOGGING
    _level = constrain(level, LOG_LEVEL_SILENT, LOG_LEVEL_VERBOSE);
#endif
}

[[maybe_unused]] int Logging::getLevel() const {
#ifndef DISABLE_LOGGING
    return _level;
#else
    return 0;
#endif
}

void Logging::setShowLevel(bool showLevel) {
#ifndef DISABLE_LOGGING
    _showLevel = showLevel;
#endif
}

[[maybe_unused]] bool Logging::getShowLevel() const {
#ifndef DISABLE_LOGGING
    return _showLevel;
#else
    return false;
#endif
}

[[maybe_unused]] void Logging::setPrefix(printfunction f) {
#ifndef DISABLE_LOGGING
    _prefix = f;
#endif
}

[[maybe_unused]] void Logging::clearPrefix() {
#ifndef DISABLE_LOGGING
    _prefix = nullptr;
#endif
}

[[maybe_unused]] void Logging::setSuffix(printfunction f) {
#ifndef DISABLE_LOGGING
    _suffix = f;
#endif
}

[[maybe_unused]] void Logging::clearSuffix() {
#ifndef DISABLE_LOGGING
    _prefix = nullptr;
#endif
}

void Logging::print(const __FlashStringHelper *format, va_list args) {
#ifndef DISABLE_LOGGING
    PGM_P p = reinterpret_cast<PGM_P>(format);
// This copy is only necessary on some architectures (x86) to change a passed
// array in to a va_list.
#ifdef __x86_64__
    va_list args_copy;
    va_copy(args_copy, args);
#endif
    char c = pgm_read_byte(p++);
    for (; c != 0; c = pgm_read_byte(p++)) {
        if (c == '%') {
            c = pgm_read_byte(p++);
#ifdef __x86_64__
            printFormat(c, &args_copy);
#else
            printFormat(c, &args);
#endif
        } else {
            _logOutput->print(c);
        }
    }
#ifdef __x86_64__
    va_end(args_copy);
#endif
#endif
}

void Logging::print(const char *format, va_list args) {
#ifndef DISABLE_LOGGING
// This copy is only necessary on some architectures (x86) to change a passed
// array in to a va_list.
#ifdef __x86_64__
    va_list args_copy;
    va_copy(args_copy, args);
#endif
    for (; *format != 0; ++format) {
        if (*format == '%') {
            ++format;
#ifdef __x86_64__
            printFormat(*format, &args_copy);
#else
            printFormat(*format, &args);
#endif
        } else {
            _logOutput->print(*format);
        }
    }
#ifdef __x86_64__
    va_end(args_copy);
#endif
#endif
}

void Logging::printFormat(const char format, va_list *args) {
#ifndef DISABLE_LOGGING
    if (format == '\0') return;
    if (format == '%') {
        _logOutput->print(format);
    } else if (format == 's') {
        char *s = va_arg(*args, char *);
        _logOutput->print(s);
    } else if (format == 'S') {
        __FlashStringHelper *s = va_arg(*args, __FlashStringHelper *);
        _logOutput->print(s);
    } else if (format == 'd' || format == 'i') {
        _logOutput->print(va_arg(*args, int), DEC);
    } else if (format == 'D' || format == 'F') {
        _logOutput->print(va_arg(*args, double));
    } else if (format == 'x') {
        _logOutput->print(va_arg(*args, int), HEX);
    } else if (format == 'X') {
        _logOutput->print("0x");
        //_logOutput->print(va_arg(*args, int), HEX);
        auto h = (uint16_t) va_arg(*args, int);
        if (h < 0xFFF) _logOutput->print('0');
        if (h < 0xFF) _logOutput->print('0');
        if (h < 0xF) _logOutput->print('0');
        _logOutput->print(h, HEX);
    } else if (format == 'p') {
        auto *obj = (Printable *) va_arg(*args, int);
        _logOutput->print(*obj);
    } else if (format == 'b') {
        _logOutput->print(va_arg(*args, int), BIN);
    } else if (format == 'B') {
        _logOutput->print("0b");
        _logOutput->print(va_arg(*args, int), BIN);
    } else if (format == 'l') {
        _logOutput->print(va_arg(*args, long), DEC);
    } else if (format == 'u') {
        _logOutput->print(va_arg(*args, unsigned long), DEC);
    } else if (format == 'c') {
        _logOutput->print((char) va_arg(*args, int));
    } else if (format == 'C') {
        char c = (char) va_arg(*args, int);
        if (c >= 0x20 && c < 0x7F) {
            _logOutput->print(c);
        } else {
            _logOutput->print("0x");
            if (c < 0xF) _logOutput->print('0');
            _logOutput->print(c, HEX);
        }
    } else if (format == 't') {
        if (va_arg(*args, int) == 1) {
            _logOutput->print("T");
        } else {
            _logOutput->print("F");
        }
    } else if (format == 'T') {
        if (va_arg(*args, int) == 1) {
            _logOutput->print(F("true"));
        } else {
            _logOutput->print(F("false"));
        }
    }
#endif
}

[[maybe_unused]] Logging &Log = Logging::instance();
