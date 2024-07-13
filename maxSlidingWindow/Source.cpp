#include<vector>
#include<queue>

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
{
	std::deque<int> dq;
	std::vector<int> ans;
	if(nums.size()==1 && k==1)
	{
		ans.push_back(nums[0]);
			return ans;
	}
	for (int i = 0; i < nums.size(); i++)
	{
		if (!dq.empty() && dq.front() <= i - k)
		{
			dq.pop_front();
		}
		while (!dq.empty() && nums[i] > nums[dq.back()])
		{
			dq.pop_back();
		}
		dq.push_back(i);
		if (i >= k - 1)
		{
			ans.push_back(nums[dq.front()]);
		}
	}
	return ans;
}
int main()
{
	std::vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
	int k = 3;
	maxSlidingWindow(nums, 3);
}