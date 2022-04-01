
#ifndef STACK_OF_POINTERS_H
#define	STACK_OF_POINTERS_H

#include <array>

	enum class StackResults {
		OK = 1,
		IS_EMPTY = 0,
		OVERFULL_ERROR = -1,
		OUT_OF_SCOPE_ERROR = -2
	};

	using STACK_ERROR_CALLBACK = void (*)(uint32_t stackID, StackResults result);

	template <typename T_StackItem, size_t L>
	class StackOfPointers {

		private:
			std::array<T_StackItem, L> stackArray = {stackArray[0] = NULL};
			uint32_t stackSizeMax = L;
			STACK_ERROR_CALLBACK errorCallback = NULL;
			uint32_t stackSizeActual = 0;
			uint32_t stackID = 0;
		public:

			StackOfPointers(uint32_t ID, STACK_ERROR_CALLBACK callBack)
			{
				stackID = ID;
				errorCallback = callBack;
			};
			~StackOfPointers() = default;

		StackResults Reset();
		bool IsEmpty();
		uint32_t GetActualSize();
		StackResults Push(T_StackItem itemToPush);
		StackResults Pop(T_StackItem* pPopedItem);
		StackResults GetByIndex(T_StackItem* pGottenItem, uint32_t index);

	};
#endif	/* STACK_OF_POINTERS_H */
