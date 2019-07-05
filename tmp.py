class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        if not nums:
            return 0

        new_tail = -1
        for i in range(len(nums)):
            if nums[i] != val:
                new_tail += 1
                nums[new_tail] = nums[i]
        return new_tail + 1