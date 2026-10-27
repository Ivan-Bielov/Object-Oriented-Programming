// Захист від повторного підключення заголовка
#pragma once

#include <string>

// Інваріант Album:
// 1. title_ коректний за форматом (isValidText) і не порожній;
// 2. artist_ коректний за форматом (isValidText) і не порожній;
// 3. рік випуску year_ у діапазоні [kMinYear, kMaxYear];
// 4. totalTracks_ у діапазоні [0, kMaxTracks];
// 5. 0 <= freeTracks_ <= totalTracks_ (зв'язок між двома полями).
class Album {
public:
    // Псевдонім типу в області видимості класу: усі лічильники
    // треків мають тип Count, змінити його можна в одному місці
    using Count = int;

    // Статичні константи: спільні для всіх об'єктів
    static constexpr int kMinYear = 1900;
    static constexpr int kMaxYear = 2026;
    static constexpr int kMaxTextLength = 100;
    static constexpr Count kMaxTracks = 200;

    // Статичний метод: перевіряє формат тексту, об'єкт не потрібен,
    // викликається як Album::isValidText(...)
    static bool isValidText(const std::string& text);

    // ----- Константні методи читання (не змінюють об'єкт) -----
    // Рядки повертаються як const&, щоб не копіювати і не дати
    // змінити поле ззовні
    const std::string& title() const;
    const std::string& artist() const;
    // Числа повертаються за значенням
    int year() const;
    Count totalTracks() const;
    Count freeTracks() const;

    // ----- Обчислювальні методи (нічого не зберігають) -----
    // Скільки треків доступні лише за передплатою
    Count paidTracks() const;
    // Чи є хоча б один безкоштовний трек
    bool hasFreeTracks() const;
    // Чи всі треки альбому безкоштовні
    bool isFullyFree() const;

    // ----- Змінювальні методи з перевіркою аргументів -----
    // Повертають true, якщо зміну виконано, і false, якщо аргумент
    // некоректний (тоді стан об'єкта не змінюється)
    bool setTitle(const std::string& title);
    bool setArtist(const std::string& artist);
    bool setYear(int year);
    // Операції предметної області для пов'язаних полів
    bool addTracks(Count n);  // додає n платних треків
    bool makeTrackFree();     // один платний трек стає безкоштовним
    bool makeTrackPaid();     // один безкоштовний трек стає платним

    // Публічна обгортка, щоб тести могли перевірити інваріант
    // (сам checkInvariant приватний)
    bool isValid() const;

private:
    // Перевіряє весь інваріант одразу, по одній умові на пункт
    bool checkInvariant() const;

    // Поля приватні, з підкресленням у кінці імені;
    // вбудовані типи мають ініціалізатор за замовчуванням
    std::string title_;
    std::string artist_;
    int year_ = kMinYear;
    Count totalTracks_ = 0;
    Count freeTracks_ = 0;
};