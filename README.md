# Stack of pointers module #

	The module ensures a push - pop stack operations for data with preset type.
In addition, it provides an random access to stored data. It can be used for various applications like sorting and storing algorithm.
 
The module provide size control and overfilling control.

All functionality is covered by `Google Tests`.

## How to use ##

 Before using it, is necessary create a stack with chosen type of pointerrs and size:
 	StackOfPointers<ItemsType*, ItemsMax> stack();
 In case callback for error handling is used, set callback and stack ID during creating the stack.
 	StackOfPointers<ItemsType*, ItemsMax> stack(1, StackErorrHandler);
 

## Functions of the module ##

> StackResults Reset()

Is used every time, when you need erase the stack.
**Return result:** enum with **OK** or an error.

---

> bool IsEmpty()

Is used to check emptiness of the stack. 
**Return value:** _true_ or _false_.

---

> uint32_t GetActualSize();

Is used to get actual size of stack(nuber of pushed items). 
**Return value:** uint32_t.

---

> StackResults Push (StackItem_t pushedItem)

Push an item to the stack.

**Return result:** enum with **OK** or an error, in addition provides a callback with **OVERFULL_ERROR**.

---

> StackResults Pop (StackItem_t* pPopedItem)

Pop an item from the stack.

**Return result:** enum with **OK** or **IS_EMPTY** or an error.

---

> StackResults GetByIndex (StackItem_t* pGottenItem, uint32_t index)

Provide access to an item from the stack by an index.
The lowest index of item in the stack starts with 1.

**Return result:** enum with **OK** or an error, in addition provides a callback with **OUT_OF_SCOPE_ERROR**.

---