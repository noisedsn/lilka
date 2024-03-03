---@meta

---@class lilka
lilka = {}

---Ця функція автоматично викликається один раз при запуску програми.
---
---Ви повинні визначити її в своєму коді, якщо ви хочете використовувати її для ініціалізації вашої програми.
---lilka.init fun()
---Ця функція автоматично викликається кожен кадр. Тут виконується ігрова логіка. В параметрі delta передається час, який пройшов з останнього кадру.
---
---Ви повинні визначити її в своєму коді, якщо ви хочете використовувати її для оновлення вашої програми.
---lilka.update fun(delta: number)
---Ця функція автоматично викликається після `lilka.update`. Тут відбувається відображення графіки.
---
---Ви повинні визначити її в своєму коді, якщо ви хочете використовувати її для малювання вашої програми.
---lilka.render fun()

return lilka
