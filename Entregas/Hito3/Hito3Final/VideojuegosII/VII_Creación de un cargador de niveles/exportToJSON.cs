using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class exportToJSON : MonoBehaviour {

	public initialProperties_Lab21 properties; //Creado para unir con el otro Script

	// Use this for initialization
	void Start () {
		//Debug.Log (tag); //cout de unity --- ejemplo

		string text;
		text = ""; //inicilizar el texto

		text += "{" +
			"\n\"elements\" :[\n" +
			"\t{ \"element-id\": \"Wall\"  , \"mesh\": \"media/pared01\" }, \n" +
			"\t{ \"element-id\": \"Floor\" , \"mesh\": \"media/pared01\" }, \n" +
			"\t{ \"element-id\": \"PlayerStart\"  , \"mesh\": \"media/dog\" }\n\t], \n" +
			"\"levels\": [\n";

		//LEVELS
		for (int k = 0; k < transform.childCount; k++) {
			var room = transform.GetChild (k);

			text += "\t{\n\t\t\"level-id\":" + k + ",\n" +
					"\t\t\"level-name\":\"" + room.name + "\",\n";
					//"\"elements\": [\n" +
					//"{ \"element-id\":" + "THETAG" + ", \"mesh\":" + "\"path/to/mesh.ext\"" +  "},\n"
		
			//SECTIONS
			for (int i = 0; i < room.childCount; i++) { 
				var section = room.GetChild (i);

				text += "\t\t\"" + section.name + "\": [\n";
				//Debug.Log ("Name: " + section.name + " ------- Childs: " + section.childCount);

				//ELEMENTS
				if (section.childCount != 0) {
					for (int j = 0; j < section.childCount; j++) {
						var child = section.GetChild (j);

						text += "\t\t\t{ \"element-id\": \"" + child.tag + "\",\n" +
							"\t\t\t\t\"position\": { \"x\":" + child.position.x + ", \"y\":" + child.position.y + ", \"z\":" + child.position.z + " },\n" +
							"\t\t\t\t\"rotation\": { \"x\":" + child.rotation.eulerAngles.x + ", \"y\":" + child.rotation.eulerAngles.y + ", \"z\":" + child.rotation.eulerAngles.z + " }}";
						/*
						//STATE
						if(child.GetComponent<initialProperties_Lab21>()!=null){
							properties = child.GetComponent<initialProperties_Lab21> ();
							Debug.Log("JJAJAJA: " + properties.state);
							Debug.Log("JJAJAJA: " + properties.Comentario);
						}
						*/

						//CLOSING
						if (i == room.childCount - 1) { //SI ES LA ULTIMA HABITACION
							/*if (k != transform.childCount) {
								text += "-------------------------------------\n";
								text += "\n\t\t]\n\t},\n";
							} else {
								text += "+++++++++++++++ \n";
								text += "\n\t]}\n";
							}
							*/
							//2ªiteracion... incluido viendo errores (al incluir puertas en initial-entities
							if (j == section.childCount - 1) {
								text += "\n\t\t]\n\t},\n";
							} else {
								text += ",\n";
							}
						} else { //SI NO ES LA ULTIMA HABITACION
							if (j == section.childCount - 1) {
								text += "\n\t\t],\n";
							} else {
								text += ",\n";
							}
						}
					}
				} else {


					if (i != room.childCount - 1) {
						text += "\t\t],\n";
					} else {
						text += "\t\t]\n";
						if (k != transform.childCount-1) {
							text += "\n\t},\n";
						}
					}
				}
			}
		}

		text += "\t}\n]}";

		//Crear y escribir un archivo de texto
		System.IO.File.WriteAllText ("unityText.json", text);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}