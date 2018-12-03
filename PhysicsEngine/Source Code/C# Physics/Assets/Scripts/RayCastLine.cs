using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayCastLine : MonoBehaviour
{
    //public float weaponRange = 50.0f;
    public RaycastHit hit;
    //private GameObject turret;
    public GameObject player;
    public Ragdoll ragdoll;
    public float timer = 5;
    public float count = 0;
    public ParticleSystem particle;

	// Use this for initialization
	void Start ()
    {
	}

    // Update is called once per frame

    private void OnDrawGizmos()
    {
        Gizmos.DrawLine(this.transform.position, this.transform.position + (this.transform.right * 5000));

    }

    void Update()
    {
        if (Physics.Raycast(this.transform.position, this.transform.right, out hit) && timer <= count)
        {
            if (ragdoll.ragdollOn == false)
            {
                Debug.Log(hit.collider.gameObject.name);
                if (hit.transform.gameObject == player)
                {
                    ragdoll.ragdollOn = true;
                    count = 0;
                    particle.GetComponent<ParticleSystem>().Play();
                }
            }
        }
        else
        {
            count += Time.deltaTime;
        }
    }

    //private void OnTriggerEnter(Collision collision)
    //{
        
    //}
}
