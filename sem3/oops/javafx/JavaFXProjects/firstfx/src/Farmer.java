import java.util.*;

public class Farmer {
    private String name;
    private List<Cattle> cattleList = new ArrayList<>();
    private List<String> auditLogs = new ArrayList<>();

    public Farmer(String name) {
        this.name = name;
        auditLogs.add("Farmer " + name + " registered.");
    }

    public String getName() {
        return name;
    }

    public void registerCattle(Cattle cattle) {
        cattleList.add(cattle);
        auditLogs.add("Cattle registered: " + cattle.getBreed());
    }

    public List<Cattle> getCattleList() {
        return cattleList;
    }

    public void fileClaim(String reason) {
        auditLogs.add("Claim filed: " + reason);
    }

    public String getAuditLogs() {
        return String.join("\n", auditLogs);
    }
}
