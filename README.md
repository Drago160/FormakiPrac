# FormakiPrac

## Чтобы посавить проект себе локально :  
git clone git@github.com:Drago160/FormakiPrac.git  
cd FormalkiPrac  

## Для сборки проекта пишите в корне в консоли :
mkdir build  
cd build  
cmake ..
make  
Для запуска main(который сейчас пуст) запустите run  
Для запуска тестов зайдите в Tests/bin и запустите BasicTest  

### Хотя я настоятельно рекомендую запускать все через CLion  

## Грамматика может быть описана в нескольких форматах:  
- Формально задать:  
Терминалы: std::unordered_set<char> termianls  
Нетерминалы: std::unordered_set<char> non_termianls   
Правила: std::unordered_map<char, std::vector<std::string>> rules, где rules['B'] - это вектор из строк выводимых из B  
Стартовый: char S  
Конструктор CF_Grammar(non_termianls, terminals, rules, S) G;

- Задать строкой вида: "S->AaB|BcA;A->cBa|aab|;B->AAB|Aa|a|aa|aaa|;" (см тесты)  

- Задать в виде CF_Grammar(N, Sigma, P, S)  
Тут:  
N - ветор нетерминалов  
Sigma - вектор терминалов  
P - ветор векторов string-ов, где каждый внутренний ветор имеет под нулевым индексом нетерминал, а все остальные строки - выводимые из него слова  
S - просто char - начальный символ.  


## Краткое описание:  
- Алгорит Эрли исполняется классом EarleyManager-ом  
- earleyRecognize просто создает объект класса EarleyManager и исполняет для него нужный метод  
