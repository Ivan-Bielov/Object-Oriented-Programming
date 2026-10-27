#include "album.h"



// Текст коректний, якщо він не порожній, не довший за ліміт і не
// починається та не закінчується пробілом
bool Album::isValidText(const std::string& text) {
    if (text.empty() || text.size() > kMaxTextLength) {
        return false;
    }
    return text.front() != ' ' && text.back() != ' ';
}


// Кожен має const після дужок: обіцянка не змінювати об'єкт

const std::string& Album::title() const { return title_; }

const std::string& Album::artist() const { return artist_; }

int Album::year() const { return year_; }

Album::Count Album::totalTracks() const { return totalTracks_; }

Album::Count Album::freeTracks() const { return freeTracks_; }



// Платні = усього - безкоштовні. Окреме поле не зберігаємо, щоб воно
// ніколи не розійшлося з двома іншими
Album::Count Album::paidTracks() const { return totalTracks_ - freeTracks_; }

bool Album::hasFreeTracks() const { return freeTracks_ > 0; }

// Порожній альбом (0 треків) не вважаємо «повністю безкоштовним»
bool Album::isFullyFree() const {
    return totalTracks_ > 0 && freeTracks_ == totalTracks_;
}

// ---------- Змінювальні методи ----------

// Спочатку перевірка, потім присвоєння: при відмові поле не чіпаємо
bool Album::setTitle(const std::string& title) {
    if (!isValidText(title)) {
        return false;
    }
    title_ = title;
    return true;
}

bool Album::setArtist(const std::string& artist) {
    if (!isValidText(artist)) {
        return false;
    }
    artist_ = artist;
    return true;
}

bool Album::setYear(int year) {
    if (year < kMinYear || year > kMaxYear) {
        return false;
    }
    year_ = year;
    return true;
}

// Додає n нових треків. Нові треки платні, тому freeTracks_ не
// змінюється. Умова n > kMaxTracks - totalTracks_ захищає від
// виходу за ліміт (і від переповнення int)
bool Album::addTracks(Count n) {
    if (n <= 0 || n > kMaxTracks - totalTracks_) {
        return false;
    }
    totalTracks_ += n;
    return true;
}

// Зробити трек безкоштовним можна, лише якщо є платний
bool Album::makeTrackFree() {
    if (paidTracks() <= 0) {
        return false;
    }
    ++freeTracks_;
    return true;
}

// Зробити трек платним можна, лише якщо є безкоштовний
bool Album::makeTrackPaid() {
    if (freeTracks_ <= 0) {
        return false;
    }
    --freeTracks_;
    return true;
}

// ---------- Інваріант ----------

bool Album::isValid() const { return checkInvariant(); }

// Умови йдуть у тому самому порядку, що й пункти інваріанта в .h
bool Album::checkInvariant() const {
    return isValidText(title_) &&                             // п. 1
        isValidText(artist_) &&                            // п. 2
        year_ >= kMinYear && year_ <= kMaxYear &&          // п. 3
        totalTracks_ >= 0 && totalTracks_ <= kMaxTracks && // п. 4
        freeTracks_ >= 0 && freeTracks_ <= totalTracks_;   // п. 5
}