import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Поиск файла times.csv в разных местах
possible_paths = [
    'results/times.csv',
    '../results/times.csv',
    '../../results/times.csv',
    '/Users/nnikich/Desktop/lab2/lab2/lab2/results/times.csv',
    '/Users/nnikich/Desktop/lab2/results/times.csv',
]

# Поиск в DerivedData
import subprocess
result = subprocess.run(['find', '/Users/nnikich/Library/Developer/Xcode/DerivedData', '-name', 'times.csv', '-type', 'f'], capture_output=True, text=True)
if result.stdout:
    for line in result.stdout.strip().split('\n'):
        if line:
            possible_paths.append(line)

csv_path = None
for path in possible_paths:
    if os.path.exists(path):
        csv_path = path
        print(f"Найден файл: {path}")
        break

if csv_path is None:
    print("Ошибка: файл times.csv не найден!")
    print("Запустите программу C++ в Xcode, чтобы создать файл.")
    exit(1)

# Чтение данных
df = pd.read_csv(csv_path)

# Создаём папку для графиков
os.makedirs('results', exist_ok=True)

# График 1: Все алгоритмы
plt.figure(figsize=(14, 8))

plt.plot(df['Size'], df['LinearSearch'], 'o-', label='Линейный поиск', linewidth=2, markersize=8)
plt.plot(df['Size'], df['BSTree'], 's-', label='Бинарное дерево (BST)', linewidth=2, markersize=8)
plt.plot(df['Size'], df['RBTree'], '^-', label='Красно-черное дерево (RBT)', linewidth=2, markersize=8)
plt.plot(df['Size'], df['HashTable'], 'd-', label='Хэш-таблица', linewidth=2, markersize=8)
plt.plot(df['Size'], df['StdMultimap'], 'v-', label='std::multimap', linewidth=2, markersize=8)

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время поиска (секунды)', fontsize=12)
plt.title('Сравнение алгоритмов поиска\nСтруктура "Преподаватели" (Вариант 5)', fontsize=14)
plt.legend(fontsize=10)
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('results/search_comparison.png', dpi=150)
plt.show()

# График 2: Только быстрые алгоритмы
plt.figure(figsize=(12, 6))

plt.plot(df['Size'], df['BSTree'], 's-', label='BST', linewidth=2, markersize=8)
plt.plot(df['Size'], df['RBTree'], '^-', label='RBT', linewidth=2, markersize=8)
plt.plot(df['Size'], df['HashTable'], 'd-', label='Hash Table', linewidth=2, markersize=8)
plt.plot(df['Size'], df['StdMultimap'], 'v-', label='std::multimap', linewidth=2, markersize=8)

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время поиска (секунды)', fontsize=12)
plt.title('Сравнение быстрых алгоритмов поиска', fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('results/fast_algorithms.png', dpi=150)
plt.show()

print("\nГрафики сохранены в results/")
print(f"Исходные данные: {csv_path}")
