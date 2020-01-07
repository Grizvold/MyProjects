package il.co.ilrd.vending_machine;
import java.util.HashMap;

/**
 * @Author      Ruslan Gorbaty
 * @Reviewer    Yuval Shlomo
 * @Group       FS767
 * @Description Vending Machine implementation.
 */

public class VendingMachine {
	
	private float currBalance = 0.0f;
	private State currState = State.INIT;
	private HashMap<Integer, MachineSlot> machineSlotMap;
	private View printStream;
	Thread vmThread;
	
	VendingMachine(View printObject){
		this.printStream = printObject;
		machineSlotMap = null;
	}
	
	public static class MachineSlot{
		private int quantity;
		private Product product;
		
		public MachineSlot() {
			this.quantity = 0;
			this.product = null;
		}
		
		public MachineSlot(int quantity, Product product)
		{
			this.quantity = quantity;
			this.product = product;
		}
		
		public void setPrice(float price) {
			this.product.setPrice(price);
		}
		
		public float getPrice() {
			return this.product.getPrice();
		}
		
		/**
		 * 
		 * @return true is empty, false if not.
		 */
		public boolean isFull() {
			return (this.quantity == this.product.getMaxPerSlot());
		}
		
		/**
		 * 
		 * @return true is empty, false if not.
		 */
		public boolean isEmpty() {
			return (this.quantity == 0);
		}

		public void setQuantity(int amount) {
			this.quantity = amount;
		}
		
		public void dispense() {			
			this.quantity--;
		}
	}
	
	public enum State{
		INIT{
			@Override
			public void allOk(VendingMachine vm){
				vm.currState = IDLE;
			}
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.printStream.print("Vending Machine is in initializing state");
			}
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				vm.printStream.print("Vending Machine is in initializing state");
			}
		},
		IDLE{
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.currBalance = amount;
				vm.currState = COLLECT_MONEY;
				vm.vmThread = vm.getNewThread();
				vm.vmThread.start();
				vm.printStream.print("Current balance: " + vm.currBalance);
			}
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				vm.printStream.print("Insert money first please");
			}
			@Override
			public void allOk(VendingMachine vm){}
		},
		COLLECT_MONEY{
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.vmThread.interrupt();
				vm.currBalance += amount;
				vm.printStream.print("Current balance: " + vm.currBalance);
				vm.vmThread = vm.getNewThread();
				vm.vmThread.start();
			}
			
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				vm.vmThread.interrupt();
				MachineSlot chosenSlot = vm.machineSlotMap.get(slotId);
				if(chosenSlot == null)
				{
					vm.printStream.print("Wrong input, try again.");
				}
				else if(vm.currBalance < chosenSlot.getPrice())
				{
					vm.printStream.print("Not enought money, missing " + 
										(chosenSlot.getPrice() - vm.currBalance));
				}
				else if(chosenSlot.isEmpty())
				{
					vm.printStream.print("Sorry, out of " + 
											chosenSlot.product.getName());
				}
				else
				{
					chosenSlot.dispense();
					vm.printStream.print("You have bought " + 
											chosenSlot.product.getName());
					vm.printStream.print("Change " + 
											(vm.currBalance - chosenSlot.product.getPrice()));
					vm.printStream.print("Thanks for the purchase");
				}
				vm.currBalance = 0.0f;
				vm.currState = IDLE;
			}
			
			@Override
			public void allOk(VendingMachine vm){}
			
		};
		
		public void insertMoney(VendingMachine vm, float amount) {}
		
		public void selectProduct(VendingMachine vm, int slotId) {}

		public void allOk(VendingMachine vm){}
	}
		
	public void slotConfiguration(HashMap<Integer, MachineSlot>machineSlotMap) {
		this.machineSlotMap = machineSlotMap;
		allOk();
	}
	
	//events
	public void insertMoney(float amount) {
		currState.insertMoney(this, amount);
	}

	public void selectProduct(int slotId) {
		currState.selectProduct(this, slotId);
	}
	
	public void allOk() {
		this.printStream.print("Ready for purchase, insert money and choose product");
		this.currState = State.IDLE;
	}
	
	public void error() {
		this.printStream.print("Sorry an error has occured");
		this.currBalance = 0.0f;
		this.currState = State.INIT;
	}
	
	private Thread getNewThread() {
		return new Thread(new Timeout());
	}
	
	public class Timeout implements Runnable{

		@Override
		public void run() {
			try {
				Thread.sleep(3000);
				currBalance = 0.0f;
				currState = State.IDLE;
				
			} catch (InterruptedException e) {
			}
		}
	}
}


