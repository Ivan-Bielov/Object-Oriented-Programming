#include <iostream>
#include <string>

#include "album.h"

namespace {

    int g_total = 0;   //скільки перевірок виконано
    int g_failed = 0;  //скільки з них провалилось

    //перевірка, буде друкувани результат тесту
    void check(bool condition, const std::string& name) {
        ++g_total;
        if (condition) {
            std::cout << "[ OK ] " << name << "\n";
        }
        else {
            ++g_failed;
            std::cout << "[FAIL] " << name << "\n";
        }
    }

    // Допоміжна функція: створює коректний альбом із 5 платними треками.
    // Конструкторів у класі ще немає, тому використовуємо сеттери
    Album makeAlbum() {
        Album a;
        a.setTitle("Abbey Road");
        a.setArtist("The Beatles");
        a.setYear(1969);
        a.addTracks(5);
        return a;
    }

    // Приймає альбом за константним посиланням: компілюється тільки тоді,
    // коли всі методи читання справді оголошені const
    void print(const Album& a) {
        std::cout << a.title() << " | " << a.artist() << " | " << a.year()
            << " | total=" << a.totalTracks() << " | free="
            << a.freeTracks() << " | paid=" << a.paidTracks() << "\n";
    }

} 

int main() {
    // 1. Щойно створений об'єкт без назви порушує інваріант 
    {
        Album a;
        check(!a.isValid(), "1. default object is invalid (empty title)");
    }

    // 2. Успішна зміна полів
    {
        Album a;
        bool ok = a.setTitle("Thriller") && a.setArtist("Michael Jackson") &&
            a.setYear(1982);
        check(ok && a.title() == "Thriller" && a.year() == 1982,
            "2. valid setters change the state");
    }

    // 3. Відхилення некоректної назви і незмінність стану
    {
        Album a = makeAlbum();
        bool r1 = a.setTitle("");
        bool r2 = a.setTitle("Abbey Road ");
        check(!r1 && !r2 && a.title() == "Abbey Road",
            "3. bad title rejected, state unchanged");
    }

    // 4. Відхилення некоректного виконавця
    {
        Album a = makeAlbum();
        bool r = a.setArtist("");
        check(!r && a.artist() == "The Beatles",
            "4. bad artist rejected, state unchanged");
    }

    // 5. Відхилення некоректного року (обидві межі)
    {
        Album a = makeAlbum();
        bool r1 = a.setYear(1899);
        bool r2 = a.setYear(2027);
        check(!r1 && !r2 && a.year() == 1969,
            "5. bad year rejected, state unchanged");
    }

    // 6. Додавання треків: коректне і некоректне
    {
        Album a = makeAlbum();
        bool r0 = a.addTracks(0);
        bool rNeg = a.addTracks(-3);
        bool rBig = a.addTracks(Album::kMaxTracks);
        bool rOk = a.addTracks(2);
        check(!r0 && !rNeg && !rBig && rOk && a.totalTracks() == 7,
            "6. addTracks rejects 0, negative, over limit");
    }

    // 7. Усі треки стають безкоштовними
    {
        Album a = makeAlbum();
        for (int i = 0; i < 5; ++i) {
            a.makeTrackFree();
        }
        check(a.isFullyFree() && a.paidTracks() == 0 && a.isValid(),
            "7. all tracks can become free");
    }

    // 8. Не можна зробити безкоштовним більше, ніж є платних
    {
        Album a = makeAlbum();
        for (int i = 0; i < 5; ++i) {
            a.makeTrackFree();
        }
        bool extra = a.makeTrackFree();
        check(!extra && a.freeTracks() == 5 && a.isValid(),
            "8. makeTrackFree with no paid tracks is rejected");
    }

    // 9. Не можна зробити платним, якщо безкоштовних немає
    {
        Album a = makeAlbum();
        bool r = a.makeTrackPaid();
        check(!r && a.freeTracks() == 0 && !a.hasFreeTracks(),
            "9. makeTrackPaid with no free tracks is rejected");
    }

    // 10. Безкоштовний і назад платний: стан відновлюється
    {
        Album a = makeAlbum();
        a.makeTrackFree();
        bool back = a.makeTrackPaid();
        check(back && a.freeTracks() == 0 && a.paidTracks() == 5,
            "10. free then paid restores the state");
    }

    // 11. Статичний метод формату викликається без об'єкта
    {
        check(Album::isValidText("Revolver") && !Album::isValidText("") &&
            !Album::isValidText(" Revolver"),
            "11. static isValidText works without an object");
    }

    // 12. Інваріант тримається після довільної послідовності викликів
    {
        Album a = makeAlbum();
        a.makeTrackFree();
        a.addTracks(3);
        a.makeTrackPaid();
        a.makeTrackPaid();  // зайвий виклик відхиляється
        a.makeTrackFree();
        a.setYear(5000);    // некоректний рік відхиляється
        check(a.isValid(), "12. invariant holds after a call sequence");
    }

    // Демонстрація print(const Album&)
    print(makeAlbum());

    std::cout << "\nTests: " << g_total << ", failed: " << g_failed << "\n";
    // Код повернення 0 означає «усе гаразд»
    return g_failed == 0 ? 0 : 1;
}