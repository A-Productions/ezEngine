
template <typename T>
EZ_FORCE_INLINE const T& ezRenderDataBatch::Iterator<T>::operator*() const
{
  return *ezStaticCast<const T*>(m_pCurrent->m_pRenderData);
}

template <typename T>
EZ_FORCE_INLINE const T* ezRenderDataBatch::Iterator<T>::operator->() const
{
  return ezStaticCast<const T*>(m_pCurrent->m_pRenderData);
}

template <typename T>
EZ_FORCE_INLINE ezRenderDataBatch::Iterator<T>::operator const T*() const
{
  return ezStaticCast<const T*>(m_pCurrent->m_pRenderData);
}

template <typename T>
EZ_FORCE_INLINE void ezRenderDataBatch::Iterator<T>::Next()
{
  ++m_pCurrent;
}

template <typename T>
EZ_FORCE_INLINE bool ezRenderDataBatch::Iterator<T>::IsValid() const
{
  return m_pCurrent < m_pEnd;
}

template <typename T>
EZ_FORCE_INLINE void ezRenderDataBatch::Iterator<T>::operator++()
{
  ++m_pCurrent;
}

template <typename T>
EZ_FORCE_INLINE ezRenderDataBatch::Iterator<T>::Iterator(const SortableRenderData* pStart, const SortableRenderData* pEnd)
{
  m_pCurrent = pStart;
  m_pEnd = pEnd;
}


EZ_FORCE_INLINE ezUInt32 ezRenderDataBatch::GetCount() const
{
  return m_Data.GetCount();
}

template <typename T>
EZ_FORCE_INLINE const T* ezRenderDataBatch::GetData(ezUInt32 uiIndex) const
{
  return ezStaticCast<const T*>(m_Data[uiIndex].m_pRenderData);
}

template <typename T>
EZ_FORCE_INLINE ezRenderDataBatch::Iterator<T> ezRenderDataBatch::GetIterator() const
{
  return Iterator<T>(begin(m_Data), end(m_Data));
}