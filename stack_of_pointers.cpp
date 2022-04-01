

#include <stdint.h>
#include <stdbool.h>               
#include "stack_of_pointers.h"


	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	StackResults StackOfPointers<T_StackItem, L>::Reset() {

		stackArray[0] = NULL;
		stackSizeActual = 0;

		return StackResults::OK;
	}

	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	bool StackOfPointers<T_StackItem, L>::IsEmpty() {

		return stackArray[0] == NULL;
	}

	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	uint32_t StackOfPointers<T_StackItem, L>::GetActualSize() {

		return stackSizeActual;
	}

	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	StackResults StackOfPointers<T_StackItem, L>::Push(T_StackItem itemToPush) {

		uint32_t position;
		for (position = 0; position < stackSizeMax; position++) {
			if (stackArray[position] == NULL) {
				break; 
			}
		}
		if ((position == stackSizeMax) && (errorCallback != NULL)) {
			errorCallback(stackID, StackResults::OVERFULL_ERROR);

			return StackResults::OVERFULL_ERROR;
		}
		stackArray[position] = itemToPush;

		if (position < (stackSizeMax - 1)) {
			stackArray[position + 1] = NULL;
		}
		stackSizeActual = position + 1;

		return StackResults::OK;
	}

	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	StackResults StackOfPointers<T_StackItem, L>::Pop(T_StackItem* pPopedItem) {

		uint32_t position;
		for (position = 0; position < stackSizeMax; position++) {
			if (stackArray[position] == NULL) {
				break; 
			}
		}
		if (position == 0) {
			stackSizeActual = position;

			return StackResults::IS_EMPTY;
		}
		position--;
		*pPopedItem = stackArray[position];
		stackArray[position] = NULL;
		stackSizeActual = position;

		return StackResults::OK;
	}

	//-------------------------------------------------------------------------------------
	template <typename T_StackItem, size_t L>
	StackResults StackOfPointers<T_StackItem, L>::GetByIndex(T_StackItem *pGottenItem, uint32_t index) {
		// the lowest numer of index is start with 1
		if (index == 0) {
			*pGottenItem = NULL;
			return StackResults::OUT_OF_SCOPE_ERROR;
		}
		index--;  
		uint32_t position;

		for (position = 0; position < stackSizeMax; position++) {
			T_StackItem nextItem = stackArray[position];
			if (nextItem == NULL) {
				break;
			}
		}
		if ((index >= position) && (errorCallback != NULL)) {
			errorCallback(stackID, StackResults::OUT_OF_SCOPE_ERROR);

			return StackResults::OUT_OF_SCOPE_ERROR;
		}
		*pGottenItem = stackArray[index];

		return StackResults::OK;
	}


/*******************************************************************************
 End of File
 */




