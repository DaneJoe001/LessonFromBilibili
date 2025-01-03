### C++ 中的 `set` 和 `unordered_set`

#### 1. **`set` 容器**
- **定义**: `std::set` 是一个关联容器，用于存储唯一的元素，并自动按升序排序。
- **特性**:
  - **唯一性**: 每个元素都是唯一的，不能重复。
  - **排序**: 默认使用 `std::less<Key>` 进行排序，可以指定自定义比较器。
  - **查找效率**: 查找、插入和删除操作的平均时间复杂度为 O(log n)。
  
- **常用操作**:
  - **插入**: `set.insert(value)`，返回一个 `pair<iterator, bool>`，其中 `bool` 表示插入是否成功。
  - **查找**: `set.find(value)`，返回指向元素的迭代器，如果未找到则返回 `end()`。
  - **计数**: `set.count(value)`，返回指定元素的个数（对于 `set`，结果只能是 0 或 1）。
  - **删除**: `set.erase(value)`，删除指定值的元素。

- **迭代器**:
  - `set` 的迭代器支持 `++` 操作，但不支持加法运算（`+`）。可以使用 `std::next` 和 `std::prev` 来进行迭代器的移动。

- **范围循环**: 可以使用范围 `for` 循环来遍历 `set` 中的元素。

#### 2. **`unordered_set` 容器**
- **定义**: `std::unordered_set` 是一个关联容器，用于存储唯一的元素，但不保证元素的顺序。
- **特性**:
  - **唯一性**: 每个元素都是唯一的，不能重复。
  - **无序性**: 元素的顺序是不确定的，基于哈希表实现。
  - **查找效率**: 查找、插入和删除操作的平均时间复杂度为 O(1)。

- **常用操作**:
  - 与 `set` 的操作类似，但由于无序性，无法保证遍历的顺序。
  
- **示例**:
  ```cpp
  std::unordered_set<int> unordered_set_01 = { 4, 5, 6, 852, 2, 4, 5, 87, 4, 5, 9 };
  ```

#### 3. **使用示例**
- 在 `check_set_container` 函数中，演示了如何使用 `set` 和 `unordered_set`：
  ```cpp
  std::set<int> set01 = { 9, 8, 5, 2, 1, 1 };
  print_array(set01); // 打印 set 的元素
  ```

- 使用 `unordered_set`：
  ```cpp
  std::unordered_set<int> unordered_set_01 = { 4, 5, 6, 852, 2, 4, 5, 87, 4, 5, 9 };
  print_array(unordered_set_01); // 打印 unordered_set 的元素
  ```

- 打印自定义提示信息：
  ```cpp
  DamnJoneUtil::print_array("unordered_set_01: ", std::cout, unordered_set_01);
  ```

#### 4. **总结**
- `set` 适用于需要保持元素顺序并且需要高效查找的场景。
- `unordered_set` 适用于对元素顺序没有要求且需要快速查找的场景。
- 两者都提供了高效的插入和删除操作，但 `set` 的查找和插入操作会受到排序的影响。