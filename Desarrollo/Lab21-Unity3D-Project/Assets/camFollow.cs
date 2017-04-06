using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class camFollow : MonoBehaviour {

	public Vector3 targetOffset;
	public Transform targetObject;
	public float velocity;

	Transform aTransform;

	// Use this for initialization
	void Start () {
		aTransform = GetComponent<Transform>();

	}
	
	// Update is called once per frame
	void Update () {
		aTransform.position = Vector3.Lerp (aTransform.position, targetObject.position + targetOffset, Time.deltaTime * velocity); 	
	}
}
