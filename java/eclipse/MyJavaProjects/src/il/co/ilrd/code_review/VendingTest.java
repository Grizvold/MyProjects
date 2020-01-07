package il.co.ilrd.code_review;

import java.util.HashMap;
import java.util.Scanner;

import il.co.ilrd.code_review.Product;
import il.co.ilrd.code_review.VendingMachine.*;
import il.co.ilrd.code_review.View;

public class VendingTest {
	
	private static HashMap<Integer, MachineSlot> machineSlotMap = new HashMap<Integer, VendingMachine.MachineSlot>();
	static Scanner userInput = new Scanner(System.in);
	
	public static void main(String[] args) {
		
		VendingMachine vm = new VendingMachine(new ViewVending());
		
		fillSlots();
		vm.slotConfiguration(machineSlotMap);

		int input = 0;
		while (input != 5) {
			System.out.println("What would you like to do?\n"
					+ "[1] - AllOk\n"
					+ "[2] - Insert Money\n"
					+ "[3] - Choose Product\n"
					+ "[4] - Error\n"
					+ "[5] - Exit\n");
			
			input = userInput.nextInt();
			
			switch (input) {
			case 1:
				vm.allOk();
				break;
			case 2:
				System.out.println("How much money would you like to insert?");
				int amount = userInput.nextInt();
				vm.insertMoney(amount);
				break;
			case 3:
				System.out.println("Choose Machine slot: \n"
						+ "[1] - coke\n"
						+ "[2] - bisli\n"
						+ "[3] - bamba\n"
						+ "[4] - water\n"
						+ "[5] - chocolate\n");
				int product = userInput.nextInt();
				vm.selectProduct(product);
				break;
			case 4:
				vm.error();
				break;
			default:
				break;
			}
		}
		
		userInput.close();
		System.out.println("Goodbye!!");
	}
	
	public static void fillSlots() {
		Product coke = new Product("coke", 10.0f, 10);
		Product bisli = new Product("bisli", 5.50f, 10);
		Product bamba = new Product("bamba", 6.5f, 15);
		Product water = new Product("water", 12.0f, 12);
		Product chocolate = new Product("chocolate", 4.0f, 10);
		
		machineSlotMap.put(1, new MachineSlot(8, coke));
		machineSlotMap.put(2, new MachineSlot(10, bisli));
		machineSlotMap.put(3, new MachineSlot(12, bamba));
		machineSlotMap.put(4, new MachineSlot(4, water));
		machineSlotMap.put(5, new MachineSlot(6, chocolate));		
	}
}

class ViewVending implements View{

	@Override
	public void print(String str) {
		System.out.println(str);
	}
}
