using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    private Rigidbody2D rb;
    private BoxCollider2D boxCollider;
    private GameManager gameManager;
    [SerializeField] private LayerMask groundLayer;

    //player movement speed
    [SerializeField] float horizontalSpeed = 7f;

    SpriteRenderer spriteRenderer;
    Color slimColor;
    //determine the x direction
    private float dirX;
    //player jump height
    public float jumpHeight = 10f;
    //to detect whether player is on the ground or not
    private bool grounded = true;

    //two states bool for animation
    [HideInInspector] public bool jumpThisFrame;
    [HideInInspector] public bool landed;
    [HideInInspector] public bool landThisFrame;


    //check in air
    float groundY;
    //flip character
    bool isFacingRight = true;


    // Start is called before the first frame update
    void Start()
    {
        //get the rigidbody and box collider of player
        rb = GetComponent<Rigidbody2D>();
        boxCollider = GetComponent<BoxCollider2D>();
        //get the sprite renderer to change the color
        spriteRenderer = GetComponent<SpriteRenderer>();
        //find the game manager
        gameManager = GameManager.findInstance();

    }

    // Update is called once per frame
    void Update()
    {
        //dirX is horintonal axis, a/d, left or right
        dirX = Input.GetAxis("Horizontal");


        //if facing right and want to move to left, or other situation flip
        if (isFacingRight && dirX < 0) flip();
        else if (!isFacingRight && dirX > 0) flip();

        //not allow to jump until 0.2s later

        rb.velocity = new Vector2(dirX * horizontalSpeed, rb.velocity.y);


        Jump();

        if (isGrounded() && rb.velocity.y > 0.1f)
        {
            landThisFrame = false;
            landed = false;
        }
    }

    private void Jump()
    {
        //if players is grounded, able to jump 
        if (isGrounded() && Input.GetButtonDown("Jump"))
        {
            //jump height is set at the front side
            rb.velocity = new Vector2(rb.velocity.x, jumpHeight);
            jumpThisFrame = true;
        }
        else if (!isGrounded() && Input.GetButtonDown("Jump")) //climb on the verticle wall
        {
            //jumpThisFrame = true;
            //if (dirX == 0)
            //{
            //    //add a velocity to push player away from the wall
            //    //rb.velocity = new Vector2(-Mathf.Sign(transform.localScale.x) * 7, 0);              
            //    //flip direction of player when jump off wall
            //    transform.localScale = new Vector3(-Mathf.Sign(transform.localScale.x), transform.localScale.y, transform.localScale.z);
            //}
            //else
            //{
            //    //add a velocity to push player away from the wall
            //    rb.velocity = new Vector2(-Mathf.Sign(transform.localScale.x) * 3, 6);
            //}

        }
        else
        {
            jumpThisFrame = false;
        }
    }

    private void OnCollisionEnter2D(Collision2D col)
    {


        //if player collide with the last platform ( in third color), they successfully pass this level
        if (col.gameObject.layer == 10)
        {
            nextLevel();

        }

        if (col.gameObject.layer == 8) //ground
        {
            landThisFrame = true;
        }


    }


    private bool isGrounded()
    {
        landed = true;
        //if the raycast hit the box under the player and is at the ground layer
        RaycastHit2D raycastHit = Physics2D.BoxCast(boxCollider.bounds.center, boxCollider.bounds.size, 0, Vector2.down, 0.1f, groundLayer);
        return raycastHit.collider != null;
    }


    //if player dies,restart this level
    private void death()
    {
        GameManager.reloadCurrent();
    }
    //load next level
    //level score plus 1
    private void nextLevel()
    {
        GameManager.loadNextScene();

    }

    private void flip()
    {
        isFacingRight = !isFacingRight;
        transform.Rotate(0f, 180f, 0f);
    }

}
