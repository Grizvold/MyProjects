package co.il.ilrd;
public class SingletonCommandFactory {
    private FactoryPattern<Command<Object>, String, Void> factory = new FactoryPattern<>();
    
    private SingletonCommandFactory() {}
    
    private static class SingletonInstance {
        private static final SingletonCommandFactory instance = new SingletonCommandFactory();
    }
    
    public static SingletonCommandFactory getInstance() {
        return SingletonInstance.instance;
    }
    
    public void add(String key, Command<Object> method) {
        factory.add(key,  (Void) -> {return method;}); 
    }
    
    public Command<Object> create(String key) {
    	return factory.create(key, null);
    }
}

