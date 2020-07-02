public class BraveKnight implements  Knight{
    private Quest quest;

    public BraveKnight(Quest quest) {
        this.quest = quest;
    }

    public Quest getQuest() {
        return quest;
    }

    //DI by setter
    public void setQuest(Quest quest) {
        this.quest = quest;
    }

    /* for example slaying some dragon */
    /* isnt coupled to any specific implementation of quest */
    public void embarkOnQuest() {
        quest.embark();
    }
}
