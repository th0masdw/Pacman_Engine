#pragma once

template<class T>
class ObjectPool final
{
public:
	ObjectPool() = default;
	~ObjectPool() = default;

	void Initialize(unsigned int amount)
	{
		if (m_IsInitialized)
			return;

		m_TotalAmountUnits = amount;
		m_IsInitialized = true;

		size_t sizePerUnit = sizeof(T);
		size_t totalSizePool = amount * sizePerUnit;

		//Allocate memory
		m_pMemoryBlock = static_cast<T*>(malloc(totalSizePool));
		m_pFreeHead = m_pMemoryBlock;
	}

	void DestroyPool()
	{
		if (!m_IsInitialized || !m_pMemoryBlock)
			return;

		Flush();

		//Deallocate memory
		free(m_pMemoryBlock);
		m_pMemoryBlock = nullptr;
	}

	void Flush()
	{
		//Reset object, keep memory
		T* pCurrent = m_pMemoryBlock;
		for (unsigned int i = 0; i < m_CurrentAmountInUse; ++i) {
			pCurrent->~T();
			++pCurrent;
		}
		m_pFreeHead = m_pMemoryBlock;
		m_CurrentAmountInUse = 0;
	}	

	T* GetAvailableUnit()
	{
		if (!m_IsInitialized || m_CurrentAmountInUse == m_TotalAmountUnits)
			return nullptr;

		T* pAvailableUnit = nullptr;
		pAvailableUnit = new (m_pFreeHead) T();
		++m_pFreeHead;
		++m_CurrentAmountInUse;
		return pAvailableUnit;
	}

private:
	T* m_pMemoryBlock = nullptr;
	T* m_pFreeHead = nullptr;
	unsigned int m_TotalAmountUnits = 0;
	unsigned int m_CurrentAmountInUse = 0;
	bool m_IsInitialized = false;
};