#pragma once
#include <initializer_list>
#include <iostream>
#include <cstdlib>      // для рандома
#include <ctime>
#include <string>       // для std::getline
#include <sstream>      // для std::istringstream

#define MEM_STEP 15     //шаг: сколько выделяется ячеек памяти минимум при добавлении эл-тов

template <typename vector_type>
class Vector;

template <typename vector_type>
class MemData {
    vector_type* _data;        // хранилище данных
    size_t _size;              // размер заполненной части хранилища
    size_t _capacity;          // вместимость хранилища

public:
    //конструкторы
    MemData(size_t size = 0);                       // по размеру + по умолчанию
    MemData(std::initializer_list<vector_type>);    // по списку инициализации
    MemData(const vector_type*, size_t);            // инициализации
    MemData(const MemData&);                        // копирования
    MemData(MemData&&) noexcept;                    // с move-семантикой
    //деструктор
    ~MemData();

    //публичные методы проверок
    inline bool is_empty() const noexcept {         // на пустоту
        return (_size == 0);
    }

    //геттеры
    inline size_t get_size() const noexcept {                           // размера
        return _size;
    }
    inline size_t get_capacity() const noexcept {                       // вместимости
        return _capacity;
    }
    inline const vector_type* const get_data_const() const noexcept {   // хранилища (возвр указ-ль по которому НЕЛЬЗЯ менять)
        return _data;
    }
    inline vector_type* const get_data_changeable() noexcept {          // хранилища (возвр указ-ль по которому МОЖНО менять)
        return _data;
    }

    //сеттеры памяти и размера заполненной части
    void set_memory(size_t) noexcept;                           // установка памяти без сохранения данных
    void reset_memory(size_t size, size_t start_index = 0);     // перевыделение памяти с сохранением данных (УБРАН NOEXCEPT)
    void clear_memory() noexcept;                               // очистка памяти
    inline void set_size(size_t size) {                         //установка размера заполненной части
        if (size > _capacity) {
            throw std::invalid_argument("ERROR: Size is bigger than capacity!");
        }
        else {
            _size = size;
        }
    }

    //операторы
    MemData& operator=(const MemData&) noexcept;         // присваивания
    MemData& operator=(MemData&&) noexcept;              // присваивания с move-семантикой
    bool operator==(const MemData&) const noexcept;      // сравнения

    //друзьяшки:
    //-функции
    template <typename vector_type> //<----иначе не компилируется
    friend void quick_sort(MemData<vector_type>& md);            // сортировки
    template <typename vector_type>
    friend void shuffle(MemData<vector_type>&);                  // перемешивания

    //-классы
    friend class Vector<vector_type>;

private:
    //служебные методы
    inline bool is_full() const noexcept {      // проверка на переполнение
        return (_size >= _capacity);
    }
};

//функции вне класса
int calculate_capacity(size_t);     //какую вместимость выставить при заданном кол-ве эл-тов
template <typename vector_type>
void quick_sort_recursive(vector_type* data, int left, int right);
template <typename vector_type>
int partition(vector_type* data, int left, int right);