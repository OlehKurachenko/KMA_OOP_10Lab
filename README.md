# NaUKMA OOP Course Lab 10

## Task

The task was to implement "Sequence" collection using array as data structure.
The following instructions were given:

> Реалізувати параметризований клас необмежених послідовностей на базі масиву. Операції над послідовностями: 
> 
> 1. Створити порожню послідовність
> 
> 2. Долучити елемент до кінця послідовності
> 
> 3. Вилучити елемент з початку послідовності
> 
> 4. Встановити належність елемента до послідовності
> 
> Корисно користуватися сигнатурою.:  
> ```cpp
> class Sequence{
>   public:
>   class BadSeq;
>   explicit Sequence(const size_t capacity=_default);
>   ~Sequence();
>   size_t capacity() const;
>   size_t sizes() const;
>   bool empty() const;
>   bool full() const;
>   Sequence& clear();
>   const Elem& operator[](const size_t index) const;
>   Elem& operator[]( const  size_t index);
>   Sequence& add(const Elem& elem);
>   Sequence& insert(const Elem& elem, const  size_t index);
>   Sequence& cut();
>   Sequence& remove();
>   bool contains(const Elem & elem);
>   private:
>   size_t _size;
>   static const size_t _default=0;
>   Array<Elem> * _allocator;
>   void reduce(const size_t times=2);
>   void enlarge(const size_t times=2);
>   Sequence& doinsert(const Elem& elem,const size_t index);
>   Sequence& doremove();
>   Sequence (const Sequence&);
>   Sequence& operator=(const Sequence&);
> };
> ```

## Comments to Task

...nothing yet.
  
