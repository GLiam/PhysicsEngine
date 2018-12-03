using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DragonBall : MonoBehaviour
{
    
    private void OnTriggerEnter(Collider other)
    {
        //Destroy(other.GetComponentInChildren<BoxCollider>());
        Destroy(other.gameObject);
    }
}
