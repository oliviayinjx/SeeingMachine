using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Deadzone : MonoBehaviour
{
    private playerTeleporter playerTeleporter;
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
        if (collision.CompareTag("Player"))
        {
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            collision.gameObject.transform.position = collision.gameObject.GetComponent<playerTeleporter>().lastTeleport.GetComponent<teleport>().GetDestination().position;
        }
    }
}
