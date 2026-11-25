#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe &other) : vectorData(other.vectorData), dequeData(other.dequeData)
{

}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		vectorData = other.vectorData;
		dequeData = other.dequeData;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{

}

void PmergeMe::parseInput(int ac, char **av, bool useVector)
{
	int i = 1;

	while (i < ac)
	{
		std::stringstream stream(av[i]);
		int number;
		char extra;

		if (!(stream >> number) || (stream >> extra))
			throw std::runtime_error("Error");
		
		if (number <= 0)
			throw std::runtime_error("Error");

		if (useVector)
		    vectorData.push_back(number);
		else
		    dequeData.push_back(number);
		i++;
	}
	
}

static std::size_t findPairInsertPos(const std::vector<std::pair<int, int> > &chain,
	int value,
	std::size_t limit)
{
	std::size_t left = 0;
	std::size_t right = limit;

	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;

		if (chain[mid].second < value)
			left = mid + 1;
		else
			right = mid;
	}

	return left;
}

static std::size_t findDequePairInsertPos(const std::deque<std::pair<int, int> > &chain,
	int value,
	std::size_t limit)
{
	std::size_t left = 0;
	std::size_t right = limit;

	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;

		if (chain[mid].second < value)
			left = mid + 1;
		else
			right = mid;
	}

	return left;
}

void PmergeMe::sortVectorPairs(std::vector<std::pair<int, int> > &pairs)
{
	if (pairs.size() < 2)
		return;

	bool hasOddPair = pairs.size() % 2 != 0;
	std::pair<int, int> oddPair;

	if (hasOddPair)
		oddPair = pairs.back();

	std::vector<std::pair<int, int> > smallerPairs;
	std::vector<std::pair<int, int> > largerPairs;

	for (std::size_t i = 0; i + 1 < pairs.size(); i += 2)
	{
		if (pairs[i].second > pairs[i + 1].second)
		{
			smallerPairs.push_back(pairs[i + 1]);
			largerPairs.push_back(pairs[i]);
		}
		else
		{
			smallerPairs.push_back(pairs[i]);
			largerPairs.push_back(pairs[i + 1]);
		}
	}

	std::vector<std::pair<int, int> > originalLargerPairs(largerPairs);
	sortVectorPairs(largerPairs);

	std::vector<std::pair<int, int> > orderedSmallerPairs;
	std::vector<bool> used(originalLargerPairs.size(), false);

	for (std::size_t i = 0; i < largerPairs.size(); ++i)
	{
		for (std::size_t j = 0; j < originalLargerPairs.size(); ++j)
		{
			if (!used[j] && largerPairs[i] ==  originalLargerPairs[j])
			{
				orderedSmallerPairs.push_back(smallerPairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	smallerPairs.swap(orderedSmallerPairs);
	std::vector<std::pair<int, int> > chain;

	chain.push_back(smallerPairs[0]);
	chain.insert(chain.end(), largerPairs.begin(), largerPairs.end());

	std::vector<std::size_t> partnerPositions;

	for (std::size_t i = 0; i < largerPairs.size(); ++i)
		partnerPositions.push_back(i + 1);

	std::size_t pendingCount = smallerPairs.size() + (hasOddPair ? 1 : 0);
	std::size_t previous = 1;
	std::size_t boundary = 3;

	while (previous < pendingCount)
	{
		std::size_t last = boundary < pendingCount ? boundary : pendingCount;

		for (std::size_t n = last; n > previous; --n)
		{
			std::size_t i = n - 1;
			bool isOdd = i == smallerPairs.size();

			const std::pair<int, int> &entry = isOdd ? oddPair : smallerPairs[i];
			std::size_t limit = isOdd ? chain.size() : partnerPositions[i];
			std::size_t pos = findPairInsertPos(chain, entry.second, limit);

			chain.insert(chain.begin() + pos, entry);

			for (std::size_t j = 0; j < partnerPositions.size(); ++j)
			{
				if (partnerPositions[j] >= pos)
					++partnerPositions[j];
			}
		}

		if (last == pendingCount)
			break;

		std::size_t next = boundary + 2 * previous;
		previous = boundary;
		boundary = next;
	}
	
	pairs.swap(chain);
}

void PmergeMe::sortDequePairs(std::deque<std::pair<int, int> > &pairs)
{
	if (pairs.size() < 2)
		return;

	bool hasOddPair = pairs.size() % 2 != 0;
	std::pair<int, int> oddPair;

	if (hasOddPair)
		oddPair = pairs.back();

	std::deque<std::pair<int, int> > smallerPairs;
	std::deque<std::pair<int, int> > largerPairs;

	for (std::size_t i = 0; i + 1 < pairs.size(); i += 2)
	{
		if (pairs[i].second > pairs[i + 1].second)
		{
			smallerPairs.push_back(pairs[i + 1]);
			largerPairs.push_back(pairs[i]);
		}
		else
		{
			smallerPairs.push_back(pairs[i]);
			largerPairs.push_back(pairs[i + 1]);
		}
	}

	std::deque<std::pair<int, int> > originalLargerPairs(largerPairs);
	sortDequePairs(largerPairs);

	std::deque<std::pair<int, int> > orderedSmallerPairs;
	std::deque<bool> used(originalLargerPairs.size(), false);

	for (std::size_t i = 0; i < largerPairs.size(); ++i)
	{
		for (std::size_t j = 0; j < originalLargerPairs.size(); ++j)
		{
			if (!used[j] && largerPairs[i] ==  originalLargerPairs[j])
			{
				orderedSmallerPairs.push_back(smallerPairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	smallerPairs.swap(orderedSmallerPairs);
	std::deque<std::pair<int, int> > chain;

	chain.push_back(smallerPairs[0]);
	chain.insert(chain.end(), largerPairs.begin(), largerPairs.end());

	std::deque<std::size_t> partnerPositions;

	for (std::size_t i = 0; i < largerPairs.size(); ++i)
		partnerPositions.push_back(i + 1);

	std::size_t pendingCount = smallerPairs.size() + (hasOddPair ? 1 : 0);
	std::size_t previous = 1;
	std::size_t boundary = 3;

	while (previous < pendingCount)
	{
		std::size_t last = boundary < pendingCount ? boundary : pendingCount;

		for (std::size_t n = last; n > previous; --n)
		{
			std::size_t i = n - 1;
			bool isOdd = i == smallerPairs.size();

			const std::pair<int, int> &entry = isOdd ? oddPair : smallerPairs[i];
			std::size_t limit = isOdd ? chain.size() : partnerPositions[i];
			std::size_t pos = findDequePairInsertPos(chain, entry.second, limit);

			chain.insert(chain.begin() + pos, entry);

			for (std::size_t j = 0; j < partnerPositions.size(); ++j)
			{
				if (partnerPositions[j] >= pos)
					++partnerPositions[j];
			}
		}

		if (last == pendingCount)
			break;

		std::size_t next = boundary + 2 * previous;
		previous = boundary;
		boundary = next;
	}
	
	pairs.swap(chain);
}

void PmergeMe::sortVector()
{
	if (vectorData.size() < 2)
		return;

	bool hasOdd = vectorData.size() % 2 != 0;
	int oddValue = 0;

	if (hasOdd)
		oddValue = vectorData.back();
	
	std::vector <std::pair<int, int> > pairs;
	for (std::size_t i = 0; i + 1 < vectorData.size(); i += 2)
	{
		int first = vectorData[i];
		int second = vectorData[i + 1];

		if (first > second)
		{
			int tmp = first;
			first = second;
			second = tmp;
		}
		pairs.push_back(std::make_pair(first, second));
	}

	sortVectorPairs(pairs);

	std::vector<int> chain;
	std::vector<std::size_t> partnerPositions;

	chain.push_back(pairs[0].first);
	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		partnerPositions.push_back(chain.size());
		chain.push_back(pairs[i].second);
	}

	std::size_t pendingCount = pairs.size() + (hasOdd ? 1 : 0);
	std::size_t previous = 1;
	std::size_t boundary = 3;

	while (previous < pendingCount)
	{
		std::size_t last = boundary < pendingCount ? boundary : pendingCount;

		for (std::size_t n = last; n > previous; --n)
		{
			std::size_t i = n - 1;
			bool isOdd = i == pairs.size();
			int value = isOdd ? oddValue : pairs[i].first;
			std::size_t limit = isOdd ? chain.size() : partnerPositions[i];
			std::vector<int>::iterator where =
				std::lower_bound(chain.begin(), chain.begin() + limit, value);
			std::size_t pos = where - chain.begin();

			chain.insert(where, value);
			for (std::size_t j = 0; j < partnerPositions.size(); ++j)
			{
				if (partnerPositions[j] >= pos)
					++partnerPositions[j];
			}
		}

		if (last == pendingCount)
			break;

		std::size_t next = boundary + 2 * previous;
		previous = boundary;
		boundary = next;
	}

	vectorData.swap(chain);
}

void PmergeMe::sortDeque()
{
	if (dequeData.size() < 2)
		return;

	bool hasOdd = dequeData.size() % 2 != 0;
	int oddValue = 0;

	if (hasOdd)
		oddValue = dequeData.back();
	
	std::deque <std::pair<int, int> > pairs;
	for (std::size_t i = 0; i + 1 < dequeData.size(); i += 2)
	{
		int first = dequeData[i];
		int second = dequeData[i + 1];

		if (first > second)
		{
			int tmp = first;
			first = second;
			second = tmp;
		}
		pairs.push_back(std::make_pair(first, second));
	}

	sortDequePairs(pairs);

	std::deque<int> chain;
	std::deque<std::size_t> partnerPositions;

	chain.push_back(pairs[0].first);
	for (std::size_t i = 0; i < pairs.size(); ++i)
	{
		partnerPositions.push_back(chain.size());
		chain.push_back(pairs[i].second);
	}

	std::size_t pendingCount = pairs.size() + (hasOdd ? 1 : 0);
	std::size_t previous = 1;
	std::size_t boundary = 3;

	while (previous < pendingCount)
	{
		std::size_t last = boundary < pendingCount ? boundary : pendingCount;

		for (std::size_t n = last; n > previous; --n)
		{
			std::size_t i = n - 1;
			bool isOdd = i == pairs.size();
			int value = isOdd ? oddValue : pairs[i].first;
			std::size_t limit = isOdd ? chain.size() : partnerPositions[i];
			std::deque<int>::iterator where =
				std::lower_bound(chain.begin(), chain.begin() + limit, value);
			std::size_t pos = where - chain.begin();

			chain.insert(where, value);
			for (std::size_t j = 0; j < partnerPositions.size(); ++j)
			{
				if (partnerPositions[j] >= pos)
					++partnerPositions[j];
			}
		}

		if (last == pendingCount)
			break;

		std::size_t next = boundary + 2 * previous;
		previous = boundary;
		boundary = next;
	}

	dequeData.swap(chain);
}

void PmergeMe::printVector() const
{
	for (std::size_t i = 0; i < vectorData.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << vectorData[i];
	}
	std::cout << std::endl;
}
