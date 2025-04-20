class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class Hashtable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * self.size

    def hash_function(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        new_node = Node(key, value)

        if self.table[index] is None:
            self.table[index] = new_node
        else:
            current = self.table[index]
            while current.next is not None:
                current = current.next
            current.next = new_node
        print(f"Inserted key={key}: value={value} at index={index}")

    def search(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        
        while current is not None:
            if current.key == key:
                print(f"Key={key} found at index={index}, value={current.value}")
                return current.value
            current = current.next
        print(f"Key={key} not found")
        return None

    def delete(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        prev = None

        while current is not None:
            if current.key == key:
                if prev is None:
                    self.table[index] = current.next
                else:
                    prev.next = current.next
                print(f"Deleted key={key} from index={index}")
                return
            prev = current
            current = current.next
        print(f"Key={key} not found to delete.")

    def display(self):
        print("index\tkey-value pairs")
        for i in range(self.size):
            current = self.table[i]
            if current is None:
                print(f"{i}\tNone")
            else:
                chain = []
                while current:
                    chain.append(f"({current.key}, {current.value})")
                    current = current.next
                print(f"{i}\t{' -> '.join(chain)}")

def main():
    size = int(input("Enter the size of the hashtable: "))
    h = Hashtable(size)

    while True:
        print("\nSelect an option:")
        print("1. Insert a key-value pair")
        print("2. Search for a key")
        print("3. Delete a key")
        print("4. Display hashtable")
        print("5. Exit")

        choice = int(input("Enter your choice: "))
        if choice == 1:
            key = int(input("Enter key: "))
            value = input("Enter value: ")
            h.insert(key, value)
        elif choice == 2:
            key = int(input("Enter key to search: "))
            h.search(key)
        elif choice == 3:
            key = int(input("Enter key to delete: "))
            h.delete(key)
        elif choice == 4:
            h.display()
        elif choice == 5:
            print("Exiting...")
            break
        else:
            print("Invalid choice, please try again.")

if __name__ == "__main__":
    main()