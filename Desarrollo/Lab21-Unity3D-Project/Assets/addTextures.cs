using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class addTextures : MonoBehaviour {

	public Texture2D myTexture; // Assuming that it has been linked to a texture imported into your project by drag-n-dropping that texture onto this property using Inspector window

	// Use this for initialization
	void Start () {
		gameObject.GetComponent<Renderer>().material.mainTexture = myTexture;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
