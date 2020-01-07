package il.co.ilrd.code_review;
import java.util.HashMap;

/**
 * @author student1
 *
 */
public class VendingMachine {
	
	private float currBalance = 0.0f;
	private State currState = State.INIT;
	private HashMap<Integer, MachineSlot> machineSlotMap;
	private View printStream;
	
	Thread t1 = new Thread(new TimeOut());
	
	public VendingMachine(View printObject){
		printStream = printObject;
	}
	
	/****************************************************************/
	
	public static class MachineSlot{
		private int quantity;
		private Product product;
		
		public MachineSlot(int quantity, Product product) {
			this.product = product;
			this.quantity = quantity;
		}
		
		public void setPrice(float price) {
			product.setPrice(price);
		}
		
		public boolean isFull() {
			return product.getMaxPerSlot() == quantity;
		}
		
		public boolean isEmpty() {
			return quantity == 0;
		}

		public void setQuantity(int amount) {
			if(amount > product.getMaxPerSlot()) {
				quantity = product.getMaxPerSlot();
			} else {
				quantity = amount;				
			}
		}
		
		public void dispense() {
			--quantity;
		}
	}

	/****************************************************************/
	
	private enum State{
		INIT {
			@Override
			void insertMoney(VendingMachine vm, float amount) {
				vm.printStream.print("Machine not ready yet!");
			}
			@Override
			void allOk(VendingMachine vm) {
				vm.currState = State.IDLE;
			}
		},
		IDLE {
			@Override
			void selectProduct(VendingMachine vm, int slotId) {
				vm.printStream.print("You haven't inserted money yet!");
			}
			@Override
			void insertMoney(VendingMachine vm, float amount) {
				vm.currBalance += amount;
				vm.printStream.print("Current balance: " + vm.currBalance);
				vm.currState = State.COLLECT_MONEY;
				vm.t1 = new Thread(vm.makeToObj());
				vm.t1.start();			
			}
		},
		COLLECT_MONEY {
			@Override
			void insertMoney(VendingMachine vm, float amount) {
				vm.currBalance += amount;
				vm.printStream.print("Current balance: " + vm.currBalance);
				vm.t1.interrupt();
				vm.t1 = new Thread(vm.makeToObj());
				vm.t1.start();			
			}
			
			@Override
			void selectProduct(VendingMachine vm, int slotId) {
				if(vm.machineSlotMap.containsKey(slotId)) {
					MachineSlot currSlot = vm.machineSlotMap.get(slotId);
					
					if (!currSlot.isEmpty() && 
							vm.currBalance >= currSlot.product.getPrice()) {
						
						vm.printStream.print("Thanks for Buying " + currSlot.product.getName());
						vm.machineSlotMap.get(slotId).dispense();
						vm.printStream.print("Your change " + (vm.currBalance - currSlot.product.getPrice()));
						vm.currBalance = 0.0f;
						vm.currState = State.IDLE;
						vm.t1.interrupt();
						
					} else if(currSlot.isEmpty()) {
						
						vm.printStream.print("Sorry, we're out of " + 
								currSlot.product.getName() +
								"\nCurrent balance: " + vm.currBalance);
								vm.t1.interrupt();
								vm.t1 = new Thread(vm.makeToObj());
								vm.t1.start();								
					} else {
						vm.printStream.print("You need to insert more money" +
								"\nCurrent balance: " + vm.currBalance + 
								"\nProduct price: " + currSlot.product.getPrice());
								vm.t1.interrupt();
								vm.t1 = new Thread(vm.makeToObj());
								vm.t1.start();		
					}
				} else {
					vm.printStream.print("Slot number: " + slotId + " doesn't exist.\n");
				}
			}
		};
				
		abstract void insertMoney(VendingMachine vm, float amount); 
		
		void selectProduct(VendingMachine vm, int slotId) {
			vm.printStream.print("Can't choose product yet!\n");
		}

		void allOk(VendingMachine vm) {
			vm.t1.interrupt();
		};	
	}
	
	/****************************************************************/
	
	public void slotConfiguration(HashMap<Integer, MachineSlot>machineSlotMap) {
		this.machineSlotMap = machineSlotMap;
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
		currState = State.INIT;
		currBalance = 0;
		printStream.print("An error occured!");
		t1.interrupt();
	}
	
	private TimeOut makeToObj() {
		return new TimeOut();
	}
	
	private class TimeOut implements Runnable{
		@Override
		public void run() {
			try {
				Thread.sleep(8000);
				System.out.println("No button pushed...Press any number to continue!!");
				currBalance = 0;
				currState = State.IDLE;
			}
			catch (Exception e) {
			} 
		}
	}
}


