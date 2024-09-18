package com.medicalsoft.servicios.model;
import com.medicalsoft.rrhh.model.Medico;
import com.medicalsoft.rrhh.model.Paciente;

import java.util.Date;
public class Teleconsulta extends CitaMedica{
	private Plataforma plataforma;
	private String enlace;
	public Teleconsulta(Paciente paciente, Medico medico, Date fechaHoraAtencion, String motivoCitaMedica, Plataforma plataforma, String enlace){
		super(paciente, medico, fechaHoraAtencion, motivoCitaMedica);
		this.plataforma = plataforma;
		this.enlace = enlace;
	}
	@Override
	public String consultarDatos(){
		return super.datosCabecera() + "PLATAFORMA:" + plataforma + " - ENLACE:" + enlace + "\n";
	}
}