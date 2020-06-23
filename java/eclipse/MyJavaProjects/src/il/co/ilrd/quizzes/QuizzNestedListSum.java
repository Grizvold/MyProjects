package il.co.ilrd.quizzes;

import java.util.ArrayList;
import java.util.List;

public class QuizzNestedListSum {

	public static void main(String[] args) {
		StringBuilder nestedBuilder = new StringBuilder();
		QuizzNestedListSum testCase = new QuizzNestedListSum();
		NestedInteger nestedInteger_List_1 = testCase.new NestedInteger();
		NestedInteger nestedInteger_List_2 = testCase.new NestedInteger();
		NestedInteger nestedInteger_List_3 = testCase.new NestedInteger();
		
		nestedInteger_List_1.add(testCase.new NestedInteger(1));
		nestedInteger_List_1.add(testCase.new NestedInteger(1));
		nestedInteger_List_2.add(testCase.new NestedInteger(2));
		nestedInteger_List_2.add(testCase.new NestedInteger(2));
		nestedInteger_List_3.add(testCase.new NestedInteger(1));
		nestedInteger_List_3.add(testCase.new NestedInteger(1));
		nestedInteger_List_1.add(nestedInteger_List_2);
		nestedInteger_List_1.add(nestedInteger_List_3);
		
		System.out.println(nestedListSum(nestedInteger_List_1.getList()));
		System.out.println(nestedInteger_List_1.printNestedInteger(nestedInteger_List_1, nestedBuilder));
	}
	
	
	public static int nestedListSum(List<NestedInteger> nestedList) {
		return getSumOfNestedList(nestedList, 1);
	}
	
	private static int getSumOfNestedList(List<NestedInteger> nestedList, int depth) {
		if(nestedList == null || nestedList.size() == 0) {
			return 0;
		}
		
		int sum = 0;
		for (NestedInteger nestedInteger : nestedList) {
				if(nestedInteger.isInteger()) {
					sum += nestedInteger.getInteger() * depth;
				}
				else {
					sum += getSumOfNestedList(nestedInteger.getList(), depth + 1);
				}
		}
		return sum;
	}
	
//	NestedInteger class
	class NestedInteger{
		private List<NestedInteger> nestedList;
		private Integer regularInteger;
		
		public NestedInteger() {
			nestedList = new ArrayList<>();
		}
		
		public NestedInteger(Integer new_integer) {
			regularInteger = new_integer;
		}
		
		public NestedInteger(List<NestedInteger> list) {
			nestedList = list;
		}
		
		public void add(NestedInteger nestedInteger) {
			if(nestedInteger != null) {
				nestedList.add(nestedInteger);
			}
			else {
				nestedList = new ArrayList<>();
				nestedList.add(nestedInteger);
			}
		}
		
		public boolean isInteger() {
			return regularInteger != null;
		}
		
		public Integer getInteger() {
			return regularInteger;
		}
		
		public void setInteger(Integer integer) {
			regularInteger = integer;
		}
		
		public List<NestedInteger> getList() {
			return nestedList;
		}
		
		public String printNestedInteger(NestedInteger thisNestedInteger, StringBuilder stringBuilder) {
			if(thisNestedInteger.isInteger()) {
				stringBuilder.append(thisNestedInteger.regularInteger);
				stringBuilder.append(",");
			}
			
			stringBuilder.append("[");
			for (NestedInteger nestedInteger : thisNestedInteger.nestedList) {
				if(nestedInteger.isInteger()) {
					stringBuilder.append(nestedInteger.regularInteger);
					stringBuilder.append(",");
				}
				else {
					printNestedInteger(nestedInteger, stringBuilder);
				}
			}
//			stringBuilder.append(",");
			stringBuilder.append("]");
			
			return stringBuilder.toString();
		}
	}
}