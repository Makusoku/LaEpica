package com.medicalsoft.infraestructura.model;
import com.medicalsoft.rrhh.model.AtencionMedica;
import com.medicalsoft.rrhh.model.Medico;
import com.medicalsoft.rrhh.model.Paciente;
import com.medicalsoft.rrhh.model.TipoAtencion;

import java.util.Date;
public class ExamenDiagnostico extends AtencionMedica{
	private SalaEspecializada salaEspecializada;
	private TipoExamen tipoExamen;
	public ExamenDiagnostico(Paciente paciente, Medico medico, Date fechaHoraAtencion, SalaEspecializada salaEspecializada, TipoExamen tipoExamen){
		super(paciente, medico, fechaHoraAtencion);
		setTipoAtencion(TipoAtencion.EXAMEN_DIAGNOSTICO);
		this.salaEspecializada = salaEspecializada;
		this.tipoExamen = tipoExamen;
	}
	@Override
	public String consultarDatos(){
		return super.datosCabecera() + salaEspecializada.devolverInformacion() + "TIPO EXAMEN:" + tipoExamen + "\n";
	}
}
