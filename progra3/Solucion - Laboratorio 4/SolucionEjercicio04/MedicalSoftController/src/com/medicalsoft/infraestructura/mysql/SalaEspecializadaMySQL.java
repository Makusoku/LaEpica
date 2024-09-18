package com.medicalsoft.infraestructura.mysql;
import com.medicalsoft.config.DBManager;
import com.medicalsoft.infraestructura.dao.SalaEspecializadaDAO;
import com.medicalsoft.infraestructura.model.SalaEspecializada;
import java.sql.Connection;
import java.sql.PreparedStatement;

public class SalaEspecializadaMySQL implements SalaEspecializadaDAO{

    private PreparedStatement pst;
    private Connection con;
    private String sql;
    
    @Override
    public int insertar(SalaEspecializada salaEspecializada) {
        int resultado = 0;
        try{
            con = DBManager.getInstance().getConnection();
            sql = "INSERT INTO sala_especializada(nombre,espacio_en_m2,torre"
                    + ",piso,posee_equipamiento_imagenologia,activa) "
                    + "VALUES(?,?,?,?,?,1)";
            pst = con.prepareStatement(sql);
            pst.setString(1, salaEspecializada.getNombre());
            pst.setDouble(2, salaEspecializada.getEspacioEnMetrosCuadrados());
            pst.setString(3, String.valueOf(salaEspecializada.getTorre()));
            pst.setInt(4, salaEspecializada.getPiso());
            pst.setBoolean(5, salaEspecializada.isPoseeEquipamientoImagenologia());
            resultado = pst.executeUpdate();
        }catch(Exception ex){
            System.out.println(ex.getMessage());
        }finally{
            try{
                con.close();
            }catch(Exception ex)
            {
                System.out.println(ex.getMessage());
            }
        }
        return resultado;
    }
}