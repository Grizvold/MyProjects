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
	private HashMap<Integer, MachineSlot> machineSlotMap = null;
	private final View printStream;
	private Thread vmThread = new Thread(new Timeout());
	private boolean threadFlag = false;
	
	VendingMachine(View printObject){
		this.printStream = printObject;
	}
	
	public static class MachineSlot{
		private int quantity = 0;
		private Product product = null;
		
		public MachineSlot(int quantity, Product product)
		{
			this.quantity = quantity;
			this.product = product;
		}
		
		public void setPrice(float price) {
			product.setPrice(price);
		}
		
		public float getPrice() {
			return product.getPrice();
		}
		
		/**
		 * 				
		 * @return true is empty, false if not.
		 */
		public boolean isFull() {
			return (quantity == product.getMaxPerSlot());
		}
		
		/**
		 * 
		 * @return true is empty, false if not.
		 */
		public boolean isEmpty() {
			return (quantity == 0);
		}

		public void setQuantity(int amount) {
			if(amount > product.getMaxPerSlot())
			{
				quantity = product.getMaxPerSlot();
			}
			else 
			{				
				quantity = amount;
			}
		}
		
		public void dispense() {			
			--quantity;
		}
	}
	
	public enum State{
		INIT{
			@Override
			public void allOk(VendingMachine vm){
				handleState(vm);
				vm.currState = IDLE;
				vm.currState.handleState(vm);
			}
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.printStream.print("Vending Machine is in initializing state");
			}
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				vm.printStream.print("Vending Machine is in initializing state");
			}
			@Override
			public void handleState(VendingMachine vm) {
				vm.printStream.print("Vending Machine has been initialized and ready to use.\n");
			}
		},
		IDLE{
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.currBalance = amount;
				vm.currState = COLLECT_MONEY;
				vm.currState.handleState(vm);
				vm.printStream.print("Current balance: " + vm.currBalance);
			}
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				vm.printStream.print("Insert money first please.");
			}
			@Override
			public void handleState(VendingMachine vm) {
				vm.printStream.print("Choose Insert Money Option and insert money.\n");
			}
		},
		COLLECT_MONEY{
			@Override
			public void insertMoney(VendingMachine vm, float amount) {
				vm.currBalance += amount;
				vm.printStream.print("Current balance: " + vm.currBalance);
				handleState(vm);
			}
			
			@Override
			public void selectProduct(VendingMachine vm, int slotId) {
				MachineSlot chosenSlot = vm.machineSlotMap.get(slotId);
				if(chosenSlot == null)
				{
					vm.printStream.print("Wrong input, try again.");
					currentStateStartTime = System.currentTimeMillis();
				}
				else if(vm.currBalance < chosenSlot.getPrice())
				{
					vm.printStream.print("Not enought money, missing " + 
										(chosenSlot.getPrice() - vm.currBalance));
					currentStateStartTime = System.currentTimeMillis();
				}
				else if(chosenSlot.isEmpty())
				{
					vm.printStream.print("Sorry, out of " + 
											chosenSlot.product.getName());
					currentStateStartTime = System.currentTimeMillis();
				}
				else
				{
					chosenSlot.dispense();
					vm.printStream.print("You have bought " + 
											chosenSlot.product.getName());
					vm.printStream.print("Change " + 
											(vm.currBalance - chosenSlot.product.getPrice()));
					vm.printStream.print("Thanks for the purchase\n\n");
					vm.currBalance = 0.0f;
					vm.currState = IDLE;
				}
				
				vm.currState.handleState(vm);
			}
			
			@Override
			public void handleState(VendingMachine vm) {
				vm.printStream.print("Insert more money or choose product.");
				currentStateStartTime = System.currentTimeMillis();
			}
			
			@Override
			public void timeout(VendingMachine vm) {
				if((System.currentTimeMillis() - currentStateStartTime) >= 8000)
				{
					vm.currState = IDLE;
					vm.currBalance = 0.0f;
					vm.currState.handleState(vm);
					vm.printStream.print("No action has been taken, reseting.\n\n");
				}
			}
		};
		
		public long currentStateStartTime;
		public void timeout(VendingMachine vm) {}		
		public void handleState(VendingMachine vm) {}
		public void insertMoney(VendingMachine vm, float amount) {}		
		public void selectProduct(VendingMachine vm, int slotId) {}
		public void allOk(VendingMachine vm){}
		
	}
		
	public void slotConfiguration(HashMap<Integer, MachineSlot>machineSlotMap) {
		this.machineSlotMap = machineSlotMap;
	}
	
	public void startVendingMachine() {
		threadFlag = true;
		vmThread.start();
	}
	
	public void stopVendingMachine() {
		threadFlag = false;
		printStream.print("Shuting down vending machine.");
	}
	//events
	public void insertMoney(float amount) {
		currState.insertMoney(this, amount);
	}

	public void selectProduct(int slotId) {
		currState.selectProduct(this, slotId);
	}
	
	public void allOk() {
		currState.allOk(this);
	}
	
	public void error() {
		this.printStream.print("Sorry an error has occured");
		this.currBalance = 0.0f;
		this.currState = State.INIT;
	}
	
	public class Timeout implements Runnable{

		@Override
		public void run() {
			try {
				while (threadFlag)
				{					
					Thread.sleep(1000);
					currState.timeout(VendingMachine.this);
				}
			} catch (InterruptedException e) {}
		}
	}
}


