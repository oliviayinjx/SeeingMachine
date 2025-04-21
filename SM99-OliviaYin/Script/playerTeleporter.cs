using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerTeleporter : MonoBehaviour
{
    private GameObject currentTeleport;
    public GameObject lastTeleport;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Teleporter"))
        {
            currentTeleport = collision.gameObject;
            transform.position = currentTeleport.GetComponent<teleport>().GetDestination().position;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("Teleporter"))
        {
            if(collision.gameObject == currentTeleport)
            {
                lastTeleport = currentTeleport;
                currentTeleport = null;

            }
        }
    }
}
