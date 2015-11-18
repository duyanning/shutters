#pragma once


namespace Shutters {

	template <class key_type, class value_type>
	class SafeMap {
		typedef std::map<key_type, value_type> Map;
		Map m_map;
	public:
		value_type operator[](key_type key)
		{
			Map::iterator pos = m_map.find(key);
			if (pos != m_map.end())
				return pos->second;
			return 0;
		}

		void insert(key_type key, value_type value)
		{
			m_map[key] = value;
		}

		void erase(key_type key)
		{
			m_map.erase(key);
		}
	};

}