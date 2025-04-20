def is_valid_key(key):
    return key.isdigit() and len(key) == 10

def linear_probing(key, l_hash):
    index = int(key) % size
    if l_hash[index] == -1:
        l_hash[index] = key
    else:
        for i in range(size):
            p = (index + i) % size
            if l_hash[p] == -1:
                l_hash[p] = key
                return l_hash
        print("Table is full")
    return l_hash

def quadratic_probing(key, q_hash):
    index = int(key) % size
    if q_hash[index] == -1:
        q_hash[index] = key
    else:
        for i in range(1, size):
            p = (index + i * i) % size
            if q_hash[p] == -1:
                q_hash[p] = key
                return q_hash
        print("Table is full")
    return q_hash

def search(key, hash_table):
    count = 1
    for j in range(size):
        index = (int(key) + j) % size
        if hash_table[index] == key:
            print("Key found at index:", index)
            print("Record is:", hash_table[index])
            print("No. of comparisons:", count)
            return
        elif hash_table[index] == -1:
            print("Key not found!")
            return
        else:
            count += 1
    print("Key not found!")

size = int(input("Enter size of hash tables: "))
linear_hash = [-1] * size
quadratic_hash = [-1] * size

print("\nInitialized Hash Tables:")
print("Linear Probing Hash Table:", linear_hash)
print("Quadratic Probing Hash Table:", quadratic_hash)

ch = 0
while ch != 4:
    print("\nMenu:")
    print("1. Linear Probing Insert")
    print("2. Quadratic Probing Insert")
    print("3. Search")
    print("4. EXIT")
    
    ch = int(input("Enter Choice: "))

    if ch == 1:
        print("\nEnter 10-digit Telephone Number for Linear Probing:")
        for _ in range(size):
            key = input("Enter number: ")
            if is_valid_key(key):
                linear_probing(key, linear_hash)
                print("Updated Linear Hash Table:", linear_hash)
            else:
                print("Invalid input! Please enter a 10-digit number.")

    elif ch == 2:
        print("\nEnter 10-digit Telephone Number for Quadratic Probing:")
        for _ in range(size):
            key = input("Enter number: ")
            if is_valid_key(key):
                quadratic_probing(key, quadratic_hash)
                print("Updated Quadratic Hash Table:", quadratic_hash)
            else:
                print("Invalid input! Please enter a 10-digit number.")

    elif ch == 3:
        key = input("Enter 10-digit key to search: ")
        if is_valid_key(key):
            print("\nSearching in Linear Probing Hash Table:")
            search(key, linear_hash)
            print("\nSearching in Quadratic Probing Hash Table:")
            search(key, quadratic_hash)
        else:
            print("Invalid input! Please enter a 10-digit number.")

    elif ch == 4:
        print("Exited!")

    else:
        print("Wrong Choice!")
