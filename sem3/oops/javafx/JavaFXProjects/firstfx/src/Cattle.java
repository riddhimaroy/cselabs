public class Cattle {
    private String breed;
    private int age;
    private double weight;
    private String vaccinationStatus;

    public Cattle(String breed, int age, double weight, String vaccinationStatus) {
        this.breed = breed;
        this.age = age;
        this.weight = weight;
        this.vaccinationStatus = vaccinationStatus;
    }

    public String getBreed() {
        return breed;
    }

    public int getAge() {
        return age;
    }

    public double getWeight() {
        return weight;
    }

    public String getVaccinationStatus() {
        return vaccinationStatus;
    }
}
