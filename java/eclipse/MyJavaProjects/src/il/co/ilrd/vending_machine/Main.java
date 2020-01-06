/**
 * 
 */
package il.co.ilrd.vending_machine;

import java.util.HashMap;
import java.util.Scanner;

import il.co.ilrd.vending_machine.VendingMachine.MachineSlot;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    First_name Last_name
 * @Group       FS767
 * @Description
 */

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Main mainTest = new Main();
		View outputView = new PrintView();
		VendingMachine testVendingMachine = new VendingMachine(outputView);
		HashMap<Integer, MachineSlot> machineSlotMap = new HashMap<>(); 
		
		Product productCoke = new Product("Coke", 3.0f, 10);
		Product productKinderBueno = new Product("KinderBueno", 2.5f, 20);
		Product productSnickers = new Product("Snickers", 3.5f, 21);
		Product productTwix = new Product("Twix", 3.6f, 23);
		Product productBounty = new Product("Bounty", 3.7f, 25);
		
		machineSlotMap.put(1, new MachineSlot(5, productCoke));
		machineSlotMap.put(2, new MachineSlot(10, productKinderBueno));
		machineSlotMap.put(3, new MachineSlot(11, productSnickers));
		machineSlotMap.put(4, new MachineSlot(13, productTwix));
		machineSlotMap.put(5, new MachineSlot(15, productBounty));
		
		
		int usersMenuChoice = 0;
		float usersMoney = 0.0f;
		int usersProductId = 0;
		Scanner userChoiseScanner = new Scanner(System.in);
		
		while(usersMenuChoice != 4)
		{			
			mainTest.printMenuHeader();
			mainTest.printMenuOptions();
			
			usersMenuChoice = userChoiseScanner.nextInt();
			switch (usersMenuChoice) {
			case 0:
				System.out.println("Machine ready for use");	
				testVendingMachine.slotConfiguration(machineSlotMap);
				break;
			case 1:
				System.out.println("Please enter amount of money");
				usersMoney = userChoiseScanner.nextFloat();
				testVendingMachine.insertMoney(usersMoney);
				break;
				
			case 2:
				System.out.println("Enter your product id");
				usersProductId = userChoiseScanner.nextInt();
				testVendingMachine.selectProduct(usersProductId);
				break;
				
			case 3:
				testVendingMachine.error();
				break;
				
			case 4:
				System.out.println("Shutting down");
				break;
			default:
				break;
			}
		}
		
		userChoiseScanner.close();
	}
	
	private void printMenuHeader() {
		System.out.println("+-------------------------------------+");
		System.out.println("|      Welcome to Vending Machine     |");
		System.out.println("+-------------------------------------+");
	}
	
	private void printMenuOptions() {
		System.out.println("Please make selection: ");
		System.out.println("1. Insert money");
		System.out.println("2. Choose product");
		System.out.println("3. Error");
		System.out.println("4. Shutdown");
		System.out.println("0. Initialize machine");
	}
}

class PrintView implements View{

	@Override
	public void print(String outputString) {
		System.out.println(outputString);
	}
}