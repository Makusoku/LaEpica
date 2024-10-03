class Persona {
    private int dni;
    private String nombre;
    private double sueldo;

    public Persona () {
        sueldo = 0.0;
    }

    public Persona (int dni, String nombre, double sueldo) {
        this.dni = dni;
        this.nombre = nombre;
        this.sueldo = sueldo;
    }

    public Persona (Persona per) {
        asignar(per);
    }

    public int getDni () {
        return dni;
    }

    public void setDni(int dni) {
        this.dni = dni;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public double getSueldo() {
        return sueldo;
    }

    public void setSueldo(double sueldo) {
        this.sueldo = sueldo;
    }

    public void asignar (Persona per) {
        this.dni = per.dni;
        this.nombre = per.nombre;
        this.sueldo = per.sueldo;
    }
}