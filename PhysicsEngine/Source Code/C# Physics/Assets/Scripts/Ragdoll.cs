using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]
public class Ragdoll : MonoBehaviour
{
    private Animator animator = null;
    public List<Rigidbody> rigidbodies = new List<Rigidbody>();
    public Player player;
    public CharacterController controller;
    public float count = 0;
    public float MaxCount = 3;

    public bool ragdollOn
    {
        get { return !animator.enabled; }
        set
        {
            animator.enabled = !value;
            //foreach (Rigidbody r in rigidbodies)
            //    r.isKinematic = !value;
            player.enabled = !value;
            controller.enabled = !value;
        }
    }

	// Use this for initialization
	void Start ()
    {
        animator = GetComponent<Animator>();

        //foreach (Rigidbody r in rigidbodies)
        //    r.isKinematic = true;
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (ragdollOn == true)
        {
            if (count >= MaxCount)
            {
                ragdollOn = false;
                count = 0;
            }
            else
            {
                count += Time.deltaTime;
            }
        }
	}
}
