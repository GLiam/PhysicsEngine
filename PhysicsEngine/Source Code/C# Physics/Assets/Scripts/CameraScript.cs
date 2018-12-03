using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraScript : MonoBehaviour
{

    public Vector3 Offset;
    public GameObject beta;
	// Use this for initialization
	void Start ()
    {
        Offset = transform.position - beta.transform.position;	
	}
	
	// Update is called once per frame
	void Update ()
    {
        transform.position = beta.transform.position + Offset;
	}
}
